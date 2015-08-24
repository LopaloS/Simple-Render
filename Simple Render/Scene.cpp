#include "Scene.h"
#include <fstream>
#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>

Scene::Scene(char* pathToData)
{
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
	
		Mesh* tempMesh = getMesh((*iter)["meshName"].asString());
		GLuint tempMaterialID = getMaterialID((*iter)["materialName"].asCString());
		GLuint tempTextureID = getTextureID ((*iter)["textureName"].asCString());

		SceneObject sceneObject(tempMesh, tempMaterialID, tempTextureID, transformMat);
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

void Scene::render(mat4 viewProj)
{
	for(vector<SceneObject>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->render(viewProj);
	}
}