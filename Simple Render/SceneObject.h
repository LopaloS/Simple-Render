#include "stdafx.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, GLuint shaderID, GLuint TextureID, mat4 transMat);
	virtual void render(mat4 viewProj);

protected:
	Mesh* mesh;
	GLuint shaderID;
	GLuint textureID;

	GLuint textureSamplerID;
	GLuint mvpMatrixID;
private:
	mat4 transMat;
};
