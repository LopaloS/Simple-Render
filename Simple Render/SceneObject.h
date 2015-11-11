#include "stdafx.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, GLuint shaderID, GLuint TextureID, mat4 transMat);
	void setNormalMap(GLuint normalMapID);
	void setSpecularMap(GLuint specularMapID);
	virtual void render(mat4 viewProj, vec3 lightDir, vec3 viewPos);

protected:
	Mesh* mesh;
	GLuint shaderID;
	GLuint textureID;
	GLuint normalMapID;
	GLuint specularMapID;

	GLuint textureSamplerID;
	GLuint normalSamplerID;
	GLuint specularSamplerID;

	GLuint viewProjMatrixID;
	GLuint transMatrixID;
	GLuint lightDirID;
	GLuint viewDirID;

private:
	mat4 transMat;
};
