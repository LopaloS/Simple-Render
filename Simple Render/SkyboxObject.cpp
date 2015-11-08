#include "SkyboxObject.h"

SkyboxObject::SkyboxObject(Mesh* mesh, GLuint shaderID, GLuint textureID) 
	: SceneObject(mesh, shaderID, textureID, mat4(1))
{}

void SkyboxObject::render(mat4 viewProj) 
{
	glUseProgram(shaderID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glUniform1i(textureSamplerID, 0);

	glUniformMatrix4fv(viewProjMatrixID, 1,GL_FALSE, &viewProj[0][0]);

	mesh->draw();
}