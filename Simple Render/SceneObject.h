#include "stdafx.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, GLuint shaderID, GLuint TextureID, mat4 transMat);
	void render(mat4 viewProj);

private:
	Mesh* mesh;
	GLuint shaderID;
	GLuint textureID;
	mat4 transMat;

	GLuint textureSamplerID;
	GLuint mvpMatrixID;
};
