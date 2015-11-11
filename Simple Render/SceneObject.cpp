#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, GLuint shaderID, GLuint textureID, mat4 transMat)
{
	this->mesh = mesh;
	this->shaderID = shaderID;
	this->textureID = textureID;
	this->transMat = transMat;

	normalMapID = 0;
	normalSamplerID = 0;
	specularSamplerID = 0;
	lightDirID = 0;

	textureSamplerID = glGetUniformLocation(shaderID, "sampler");
	viewProjMatrixID = glGetUniformLocation(shaderID, "viewProj");
	transMatrixID = glGetUniformLocation(shaderID, "model");
}

void SceneObject::setNormalMap( GLuint normalMapID)
{
	this->normalMapID = normalMapID;
	normalSamplerID = glGetUniformLocation(shaderID, "normalSampler");
	specularSamplerID = glGetUniformLocation(shaderID, "specularSampler");

	lightDirID = glGetUniformLocation(shaderID, "lightDir");
	viewDirID = glGetUniformLocation(shaderID, "viewPos");
}

void SceneObject::setSpecularMap(GLuint specularMapID)
{
	this->specularMapID = specularMapID;
}

void SceneObject::render(mat4 viewProj, vec3 lightDir, vec3 viewPos)
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
	}

	if(specularSamplerID > 0)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, specularMapID);
		glUniform1i(specularSamplerID, 2);
	}

	glUniform3fv(lightDirID,1, &lightDir[0]);
	glUniform3fv(viewDirID,1, &viewPos[0]);
	glUniformMatrix4fv(viewProjMatrixID, 1,GL_FALSE, &viewProj[0][0]);
	glUniformMatrix4fv(transMatrixID, 1,GL_FALSE, &transMat[0][0]);

	mesh->draw();
}