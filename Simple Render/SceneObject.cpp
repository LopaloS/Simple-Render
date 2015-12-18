#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, bool solid, GLuint shaderID, map<string, GLuint> texures, mat4 transMat)
{
	this->mesh = mesh;
	this->solid = solid;
	this->shaderID = shaderID;
	this->texures = texures;
	this->transMat = transMat;
}

void SceneObject::render(Camera camera, DirectionLight light)
{
	if(solid)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else
		glDisable(GL_CULL_FACE);

	glUseProgram(shaderID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, light.getShadowMapID());
	glUniform1i(glGetUniformLocation(shaderID, "shadowMap"), 0);

	GLuint curTexture = GL_TEXTURE1;
	GLuint uniformLocation = 1;

	for (auto iter = texures.begin(); iter != texures.end(); iter++)
	{
		glActiveTexture(curTexture);
		glBindTexture(GL_TEXTURE_2D, iter->second);
		glUniform1i(glGetUniformLocation(shaderID, iter->first.c_str()), uniformLocation);
		curTexture++;
		uniformLocation++;
	}

	mat4 viewProj = camera.getProjMatrix() * camera.getViewMatrix();
	glUniform3fv(glGetUniformLocation(shaderID, "lightDir"),1, &light.getDirection()[0]);
	glUniform3fv(glGetUniformLocation(shaderID, "viewPos"),1, &camera.getPosition()[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "viewProj"), 1,GL_FALSE, &viewProj[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1,GL_FALSE, &transMat[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "lightSpace"), 1, GL_FALSE, &light.getLightSpace()[0][0]);

	mesh->draw();
}

void SceneObject::renderDepth(GLuint depthShaderID, DirectionLight light)
{
	if(solid)
		glCullFace(GL_FRONT);
	else
		glCullFace(GL_BACK);

	glUseProgram(depthShaderID);
	mat4 mvpMat = light.getLightSpace() * transMat;
	glUniformMatrix4fv(glGetUniformLocation(depthShaderID, "viewProjModel"), 1,GL_FALSE, &mvpMat[0][0]);
	mesh->draw();
}