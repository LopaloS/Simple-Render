#include "Scene.h"
#include <fstream>
#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>
#include <glfw3.h>

Scene::Scene(int windowWidth, int windowHeight, char* pathToData)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	GLuint skyboxID = createSkybox();
	depthShaderID = Material("Depth.glsl").getID();
	shadowFBO = new FrameBufferObject(depthMapResolution, depthMapResolution, false);
	waterReflectFBO = new FrameBufferObject(windowWidth, windowHeight, true);
	waterRefractFBO = new FrameBufferObject(windowWidth, windowHeight, true);

	meshLoader = new MeshLoader();
    Reader jsonReader;
	std::ifstream stream(pathToData);
	Value root;	
	jsonReader.parse(stream, root, false);
	waterHeight = FLT_MAX;

	for (Value::iterator iter = root.begin(); iter != root.end(); iter++)
	{
		Value rotValue = (*iter)["rotation"];
		Value posValue = (*iter)["position"];
		
		vec3 rot(rotValue[0].asFloat(), rotValue[1].asFloat(), rotValue[2].asFloat());
		mat4 transformMat = eulerAngleYXZ(radians(rot.y),radians(rot.x), radians(rot.z));

		vec3 pos(posValue[0].asFloat(), posValue[1].asFloat(), posValue[2].asFloat());
		transformMat = translate(transformMat, pos);
	
		Mesh* tempMesh = getMesh((*iter)["mesh"].asString());

		string materialName = (*iter)["material"].asCString();
		if(strstr(materialName.c_str(), "Water"))
			waterHeight = pos.y;

		GLuint tempMaterialID = getMaterialID(materialName);
		Value solidValue = (*iter)["solid"];

		vector<string> names = (*iter).getMemberNames();
		map<string, GLuint> texures;

		texures.insert(pair<string, GLuint>("shadowMap", shadowFBO->getTextureID()));
		for (int i = 0; i < names.size(); i++)
		{
			if(strstr(names[i].c_str(), "Tex"))
			{
				int texureID = getTextureID((*iter)[names[i].c_str()].asString());
				texures.insert(pair<string, GLuint>(names[i], texureID));
			}
		}
		texures.insert(pair<string, GLuint>("refractionMap", waterRefractFBO->getTextureID()));
		texures.insert(pair<string, GLuint>("reflectionMap", waterReflectFBO->getTextureID()));
		
		bool solid = solidValue.type() == NULL || solidValue.asBool();
		SceneObject sceneObject(tempMesh, solid, tempMaterialID, texures, transformMat);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shadowPass(light);
	
	glViewport(0,0, windowWidth, windowHeight);
	
	glEnable(GL_CLIP_DISTANCE0);

	
	vec4 clipPlane(0, -1, 0, waterHeight + 1);
	waterRefractFBO->activate();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mainPass(camera, light, clipPlane);
	

	clipPlane.y = 1;
	clipPlane.w = -waterHeight;
	waterReflectFBO->activate();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.setReflectedViewMatrix(waterHeight);
	mainPass(camera, light, clipPlane);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_CLIP_DISTANCE0);

	camera.setNormalViewMatrix();
	mainPass(camera, light, clipPlane);
}


void Scene::shadowPass(DirectionLight light)
{
	glViewport(0,0, depthMapResolution, depthMapResolution);
	shadowFBO->activate();
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	for(vector<SceneObject>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->renderDepth(depthShaderID, light);
	}
}

void Scene::mainPass(Camera camera, DirectionLight light, vec4 clipPlane)
{
	cubeMapObject->render(camera);
	for(vector<SceneObject>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->render(camera, light, clipPlane);
	}
}