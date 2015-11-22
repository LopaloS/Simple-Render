#include "SceneObject.h"

class SkyboxObject
	{
	public:
		SkyboxObject(Mesh* mesh, GLuint shaderID, GLuint textureID);
		void render(Camera camera);		
	private:
		Mesh* mesh;
		GLuint shaderID;
		GLuint textureID;

		GLuint textureSamplerID;
		GLuint viewProjMatrixID;
	};