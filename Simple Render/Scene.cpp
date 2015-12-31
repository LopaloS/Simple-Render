#include "Scene.h"
#include <fstream>
#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>
#include <glfw3.h>

Scene::Scene(char* pathToData)
{
	GLuint skyboxID = createSkybox();
	depthShaderID = Material("Depth.glsl").getID();

	meshLoader = new MeshLoader();
    Reader jsonReader;
	std::ifstream stream(pathToData);
	Value root;	
	jsonReader.parse(stream, root, false);

	for (Value::iterator iter = root.begin(); iter != root.end(); iter++)
	{
		Value rotValue = (*iter)["rotation"];
		Value posValue = (*iter)["position"];
		
		vec3 rot(rotValue[0].asFloat(), rotValue[1].asFloat(), rotValue[2].asFloat());
		mat4 transformMat = eulerAngleYXZ(radians(rot.y),radians(rot.x), radians(rot.z));

		vec3 pos(posValue[0].asFloat(), posValue[1].asFloat(), posValue[2].asFloat());
		transformMat = translate(transformMat, pos);
	
		Mesh* tempMesh = getMesh((*iter)["mesh"].asString());
		GLuint tempMaterialID = getMaterialID((*iter)["material"].asCString());
		Value solidValue = (*iter)["solid"];

		vector<string> names = (*iter).getMemberNames();
		map<string, GLuint> texures;
		for (int i = 0; i < names.size(); i++)
		{
			if(strstr(names[i].c_str(), "Tex"))
			{
				int texureID = getTextureID((*iter)[names[i].c_str()].asString());
				texures.insert(pair<string, GLuint>(names[i], texureID));
			}
		}
		
		bool solid = solidValue.type() == NULL || solidValue.asBool();
		SceneObject sceneObject(tempMesh, solid, tempMaterialID, texures, transformMat, skyboxID);

		sceneObjects.push_back(sceneObject);
	}
}

Mesh* Scene::getMesh(string name)
{
	if(!meshMap.count(name))
		meshMap.insert(pair<string, Mesh*>(name, meshLoader->loadMesh(name))); 
	return meshMap[name];
}

GLuint Scene::getMaterialID(string name)
{
	if (!materialMap.count(name))
	{
		Material material(name);
		materialMap.insert(pair<string, GLuint>(name, material.getID()));
	}
	return materialMap[name];
}

GLuint Scene::getTextureID(string name)
{
	if (!texturesMap.count(name))
	{
		Texture texture(name);
		texturesMap.insert(pair<string, GLuint>(name, texture.getID()));
	}
	return texturesMap[name];
}

GLuint Scene::createSkybox()
{
	vector<vec3>* vertices = new vector<vec3>();

	vertices->push_back(vec3(-1.0f,  1.0f, -1.0f));
	vertices->push_back(vec3(-1.0f, -1.0f, -1.0f));
	vertices->push_back(vec3( 1.0f, -1.0f, -1.0f));
	vertices->push_back(vec3( 1.0f, -1.0f, -1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f, -1.0f));
	vertices->push_back(vec3(-1.0f,  1.0f, -1.0f));

	vertices->push_back(vec3(-1.0f, -1.0f,  1.0f));
	vertices->push_back(vec3(-1.0f, -1.0f, -1.0f));
	vertices->push_back(vec3(-1.0f,  1.0f, -1.0f));
	vertices->push_back(vec3(-1.0f,  1.0f, -1.0f));
	vertices->push_back(vec3(-1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3(-1.0f, -1.0f,  1.0f));

	vertices->push_back(vec3( 1.0f, -1.0f, -1.0f));
	vertices->push_back(vec3( 1.0f, -1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f, -1.0f));
	vertices->push_back(vec3( 1.0f, -1.0f, -1.0f));

	vertices->push_back(vec3(-1.0f, -1.0f,  1.0f));
	vertices->push_back(vec3(-1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f, -1.0f,  1.0f));
	vertices->push_back(vec3(-1.0f, -1.0f,  1.0f));

	vertices->push_back(vec3(-1.0f,  1.0f, -1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f, -1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3(-1.0f,  1.0f,  1.0f));
	vertices->push_back(vec3(-1.0f,  1.0f, -1.0f));

	vertices->push_back(vec3(-1.0f, -1.0f, -1.0f));
	vertices->push_back(vec3(-1.0f, -1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f, -1.0f, -1.0f));
	vertices->push_back(vec3( 1.0f, -1.0f, -1.0f));
	vertices->push_back(vec3(-1.0f, -1.0f,  1.0f));
	vertices->push_back(vec3( 1.0f, -1.0f,  1.0f));

	Mesh* mesh = new Mesh(vertices, NULL, NULL);
	Material material("Skybox.glsl");
	CubeMap cubemap;
	cubeMapObject = new SkyboxObject(mesh, material.getID(), cubemap.getID());
	return cubemap.getID();
}

void Scene::render(Camera camera, DirectionLight light)
{
	cubeMapObject->render(camera);
	for(vector<SceneObject>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->render(camera, light);
	}
}

void Scene::renderDepth(DirectionLight light)
{
	for(vector<SceneObject>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->renderDepth(depthShaderID, light);
	}
}