#include "stdafx.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, GLuint shaderID, GLuint TextureID, mat4 transMat);
	void setNormalMap( GLuint normalMapID);
	virtual void render(mat4 viewProj, vec3 lightDir);

protected:
	Mesh* mesh;
	GLuint shaderID;
	GLuint textureID;
	GLuint normalMapID;

	GLuint textureSamplerID;
	GLuint normalSamplerID;
	GLuint viewProjMatrixID;
	GLuint transMatrixID;
	GLuint lightDirID;

private:
	mat4 transMat;
};
