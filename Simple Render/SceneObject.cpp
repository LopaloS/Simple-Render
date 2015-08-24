#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, GLuint shaderID, GLuint textureID, mat4 transMat)
{
	this->mesh = mesh;
	this->shaderID = shaderID;
	this->textureID = textureID;
	this->transMat = transMat;

	textureSamplerID = glGetUniformLocation(shaderID, "texture");
	mvpMatrixID = glGetUniformLocation(shaderID, "mvp");
}

void SceneObject::render(mat4 viewProj)
{
	glUseProgram(shaderID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1d(textureSamplerID, 0);

	mat4 mvp = viewProj * transMat;
	glUniformMatrix4fv(mvpMatrixID, 1,GL_FALSE, &mvp[0][0]);

	mesh->draw();
}