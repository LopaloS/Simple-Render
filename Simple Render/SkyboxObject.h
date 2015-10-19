#include "SceneObject.h"

class SkyboxObject : public SceneObject
	{
	public:
		SkyboxObject(Mesh* mesh, GLuint shaderID, GLuint textureID);
		void render(mat4 viewProj);		
	};