#include "stdafx.h"
#include "Libs\jsoncpp\json\json.h"
#include "Material.h"
#include "SkyboxObject.h"
#include "MeshLoader.h"
#include "FrameBufferObject.h"

using namespace Json;

class Scene
{

#define depthMapResolution 4096

public:
	Scene(int windowWidth, int windowHeight, char* pathToData);
	void render(Camera camera, DirectionLight light);

private:
	int windowWidth;
	int windowHeight;

	vector<SceneObject> sceneObjects; 
	map<string, Mesh*> meshMap;
	map<string, GLint> materialMap;
	map<string, GLint> texturesMap;

	GLuint depthShaderID;
	SkyboxObject* cubeMapObject;
	MeshLoader* meshLoader;

	FrameBufferObject* shadowFBO;
	FrameBufferObject* waterReflectFBO;
	FrameBufferObject* waterRefractFBO;

	Mesh* getMesh(string);
	GLuint getMaterialID(string);
	GLuint getTextureID(string);
	
	float waterHeight;

	GLuint createSkybox();
	void mainPass(Camera camera, DirectionLight light, vec4 clipPlane);
	void shadowPass(DirectionLight light);
};