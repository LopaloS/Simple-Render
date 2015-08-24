#include "Libs\jsoncpp\json\json.h"
#include "Material.h"
#include "SceneObject.h"
#include "MeshLoader.h"

using namespace Json;

class Scene
{
public:
	Scene(char* pathToData);
	void render(mat4 viewProj);


private:
	vector<SceneObject> sceneObjects; 
	map<string, Mesh*> meshMap;
	map<string, GLint> materialMap;
	map<string, GLint> texturesMap;

	MeshLoader* meshLoader;

	Mesh* getMesh(string);
	GLuint getMaterialID(string);
	GLuint getTextureID(string);
};