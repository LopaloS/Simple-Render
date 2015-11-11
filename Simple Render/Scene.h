#include "Libs\jsoncpp\json\json.h"
#include "Material.h"
#include "SkyboxObject.h"
#include "MeshLoader.h"

using namespace Json;

class Scene
{
public:
	Scene(char* pathToData);
	void render(mat4 viewMat, mat4 projMat, vec3 viewPos);


private:
	vector<SceneObject> sceneObjects; 
	map<string, Mesh*> meshMap;
	map<string, GLint> materialMap;
	map<string, GLint> texturesMap;

	SkyboxObject* cubeMapObject;

	MeshLoader* meshLoader;

	Mesh* getMesh(string);
	GLuint getMaterialID(string);
	GLuint getTextureID(string);
	
	void createCubeMapObj();
};