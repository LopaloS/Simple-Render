#include "Scene.h"
#include <fstream>
#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>
#include <glfw3.h>

Scene::Scene(int windowWidth, int windowHeight, char* pathToData)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	depthShaderID = Material("Depth.glsl").getID();
	shadowFBO = new FrameBufferObject(depthMapResolution, depthMapResolution, false);
	
	waterRefractFBO = new FrameBufferObject(windowWidth, windowHeight, true);
	waterRefractDepthFBO = new FrameBufferObject(windowWidth, windowHeight, false);
	waterReflectFBO = new FrameBufferObject(windowWidth, windowHeight, true);

	meshLoader = new MeshLoader();
	GLuint skyboxID = createSkybox();
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
		bool isWater = strstr(materialName.c_str(), "Water");

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
		
		bool solid = solidValue.type() == NULL || solidValue.asBool();
		

		if(isWater)
		{
			texures.insert(pair<string, GLuint>("refractionMap", waterRefractFBO->getTextureID()));
			texures.insert(pair<string, GLuint>("reflectionMap", waterReflectFBO->getTextureID()));
			texures.insert(pair<string, GLuint>("depthMap", waterRefractDepthFBO->getTextureID()));
			SceneObject sceneObject(tempMesh, solid, tempMaterialID, texures, transformMat);
			waterObjects.push_back(sceneObject);
			waterHeight = pos.y;
		}
		else
		{
			SceneObject sceneObject(tempMesh, solid, tempMaterialID, texures, transformMat);
			sceneObjects.push_back(sceneObject);
		}
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
	Mesh* mesh = getMesh("cube.obj");
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
	mainPass(camera, light, clipPlane);
	waterRefractDepthFBO->activate();
	depthPass(camera, clipPlane);

	clipPlane.y = 1;
	clipPlane.w = -waterHeight;
	waterReflectFBO->activate();
	camera.setReflectedViewMatrix(waterHeight);
	mainPass(camera, light, clipPlane);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_CLIP_DISTANCE0);

	camera.setNormalViewMatrix();
	mainPass(camera, light, clipPlane);
	waterPass(camera, light);
}


void Scene::shadowPass(DirectionLight light)
{
	glViewport(0,0, depthMapResolution, depthMapResolution);
	shadowFBO->activate();
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glUseProgram(depthShaderID);
	for(vector<SceneObject>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->renderShadow(depthShaderID, light);
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

void Scene::depthPass(Camera camera, vec4 clipPlane)
{
	glUseProgram(depthShaderID);
	for(vector<SceneObject>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->renderDepth(depthShaderID, camera.getProjMatrix() * camera.getViewMatrix(), clipPlane);
	}
}

void Scene::waterPass(Camera camera, DirectionLight light)
{
	for(vector<SceneObject>::iterator it = waterObjects.begin(); it != waterObjects.end(); it++)
	{
		it->render(camera, light, vec4());
	}
}