#include "stdafx.h"
#include "Libs\jsoncpp\json\json.h"
#include "Material.h"
#include "SkyboxObject.h"
#include "MeshLoader.h"

using namespace Json;

class Scene
{
public:
	Scene(char* pathToData);
	void render(Camera camera, DirectionLight light);
	void renderDepth(DirectionLight light);

private:
	vector<SceneObject> sceneObjects; 
	map<string, Mesh*> meshMap;
	map<string, GLint> materialMap;
	map<string, GLint> texturesMap;

	GLuint depthShaderID;
	SkyboxObject* cubeMapObject;
	MeshLoader* meshLoader;
	vec3 lightDir;

	Mesh* getMesh(string);
	GLuint getMaterialID(string);
	GLuint getTextureID(string);
	
	GLuint createSkybox();
};