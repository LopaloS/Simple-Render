#include "stdafx.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, GLuint shaderID, GLuint TextureID, mat4 transMat);
	void setNormalMap(GLuint normalMapID);
	void setSpecularMap(GLuint specularMapID);
	void render(Camera camera, DirectionLight light);
	void renderDepth(GLuint depthShaderID, DirectionLight light);

private:
	Mesh* mesh;
	GLuint shaderID;
	GLuint textureID;
	GLuint normalMapID;
	GLuint specularMapID;

	GLuint textureSamplerID;
	GLuint shadowSamplerID;
	GLuint normalSamplerID;
	GLuint specularSamplerID;

	GLuint viewProjMatrixID;
	GLuint transMatrixID;
	GLuint lightDirID;
	GLuint viewDirID;
	GLuint lightSpaceID;

	mat4 transMat;
};
