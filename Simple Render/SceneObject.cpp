#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, GLuint shaderID, GLuint textureID, mat4 transMat)
{
	this->mesh = mesh;
	this->shaderID = shaderID;
	this->textureID = textureID;
	this->transMat = transMat;

	normalMapID = 0;
	normalSamplerID = 0;
	lightDirID = 0;

	textureSamplerID = glGetUniformLocation(shaderID, "sampler");
	viewProjMatrixID = glGetUniformLocation(shaderID, "viewProj");
	transMatrixID = glGetUniformLocation(shaderID, "model");
}

void SceneObject::setNormalMap( GLuint normalMapID)
{
	this->normalMapID = normalMapID;
	normalSamplerID = glGetUniformLocation(shaderID, "normalSampler");
	lightDirID = glGetUniformLocation(shaderID, "lightDir");
}

void SceneObject::render(mat4 viewProj, vec3 lightDir)
{
	glUseProgram(shaderID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(textureSamplerID, 0);

	if(normalMapID > 0 && textureSamplerID > 0)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMapID);
		glUniform1i(normalSamplerID, 1);
		glUniform3fv(lightDirID,1, &lightDir[0]);
	}

	glUniformMatrix4fv(viewProjMatrixID, 1,GL_FALSE, &viewProj[0][0]);
	glUniformMatrix4fv(transMatrixID, 1,GL_FALSE, &transMat[0][0]);

	mesh->draw();
}