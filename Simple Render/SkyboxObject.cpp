#include "SkyboxObject.h"

SkyboxObject::SkyboxObject(Mesh* mesh, GLuint shaderID, GLuint textureID) 
{
	this->mesh = mesh;
	this->shaderID = shaderID;
	this->textureID = textureID;	

	textureSamplerID = glGetUniformLocation(shaderID, "sampler");
	viewProjMatrixID = glGetUniformLocation(shaderID, "viewProj");
}

void SkyboxObject::render(Camera camera) 
{
	mat4 viewProj = camera.getProjMatrix() * mat4(mat3(camera.getViewMatrix()));
	glUseProgram(shaderID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glUniform1i(textureSamplerID, 0);

	glUniformMatrix4fv(viewProjMatrixID, 1,GL_FALSE, &viewProj[0][0]);

	mesh->draw();
}