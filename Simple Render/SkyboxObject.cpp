#include "SkyboxObject.h"

SkyboxObject::SkyboxObject(Mesh* mesh, GLuint shaderID, GLuint textureID) 
{
	this->mesh = mesh;
	this->shaderID = shaderID;
	this->textureID = textureID;	
}

void SkyboxObject::render(Camera camera) 
{
	glDisable(GL_CULL_FACE);
	mat4 viewProj = camera.getProjMatrix() * mat4(mat3(camera.getViewMatrix()));
	glUseProgram(shaderID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glUniform1i(glGetUniformLocation(shaderID, "sampler"), 0);

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "viewProj"), 1,GL_FALSE, &viewProj[0][0]);

	mesh->draw();
}