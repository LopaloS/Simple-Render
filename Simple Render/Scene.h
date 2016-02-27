#include "stdafx.h"
#include "Libs\jsoncpp\json\json.h"
#include "SkyboxObject.h"
#include "MeshLoader.h"

using namespace Json;

class Scene
{

#define depthMapResolution 4096

public:
	Scene(int windowWidth, int windowHeight, char* pathToData, MeshLoader* meshLoader);
	void render(Camera camera, DirectionLight light, FrameBufferObject defaultFBO);

private:
	int windowWidth;
	int windowHeight;

	vector<SceneObject> sceneObjects; 
	vector<SceneObject> waterObjects; 
	map<string, Mesh*> meshMap;
	map<string, GLint> materialMap;
	map<string, GLint> texturesMap;

	GLuint depthShaderID;
	SkyboxObject* cubeMapObject;
	MeshLoader* meshLoader;

	FrameBufferObject* shadowFBO;
	FrameBufferObject* waterRefractFBO;
	FrameBufferObject* waterRefractDepthFBO;
	FrameBufferObject* waterReflectFBO;

	Mesh* getMesh(string);
	GLuint getMaterialID(string);
	GLuint getTextureID(string);
	
	float waterHeight;

	GLuint createSkybox();
	void mainPass(Camera camera, DirectionLight light, vec4 clipPlane);
	void shadowPass(DirectionLight light);
	void depthPass(Camera camera, vec4 clipPlane);
	void waterPass(Camera camera, DirectionLight light);
};