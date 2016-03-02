#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, bool solid, GLuint shaderID, map<string, GLuint> texures, mat4 transMat)
{
	this->mesh = mesh;
	this->solid = solid;
	this->shaderID = shaderID;
	this->texures = texures;
	this->transMat = transMat;
	this->skyboxID = skyboxID;
}

void SceneObject::render(Camera camera, DirectionLight light, vec4 clipPlane)
{
	if(solid)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else
		glDisable(GL_CULL_FACE);

	glUseProgram(shaderID);


	GLuint curTexture = GL_TEXTURE0;
	GLuint uniformLocation = 0;

	for (auto iter = texures.begin(); iter != texures.end(); iter++)
	{
		glActiveTexture(curTexture);
		glBindTexture(GL_TEXTURE_2D, iter->second);
		glUniform1i(glGetUniformLocation(shaderID, iter->first.c_str()), uniformLocation);
		curTexture++;
		uniformLocation++;
	}

	glUniform4f(glGetUniformLocation(shaderID, "clipPlane"), clipPlane.x, clipPlane.y, clipPlane.z, clipPlane.w);

	mat4 viewProj = camera.getProjMatrix() * camera.getViewMatrix();
	glUniform3fv(glGetUniformLocation(shaderID, "lightDir"),1, &light.getDirection()[0]);
	glUniform3fv(glGetUniformLocation(shaderID, "viewPos"),1, &camera.getPosition()[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "viewProj"), 1,GL_FALSE, &viewProj[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1,GL_FALSE, &transMat[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "lightSpace"), 1, GL_FALSE, &light.getLightSpace()[0][0]);
	glUniform1f(glGetUniformLocation(shaderID, "time"), glfwGetTime());

	mesh->draw();
}


void SceneObject::renderShadow(GLuint depthShaderID, DirectionLight light)
{
	if(solid)
		glCullFace(GL_FRONT);
	else
		glCullFace(GL_BACK);


	renderDepth(depthShaderID, light.getLightSpace(), vec4());
}

void SceneObject::renderDepth(GLuint depthShaderID, mat4 viewProj, vec4 clipPlane)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texures["mainTex"]);
	glUniform1i(glGetUniformLocation(shaderID, "mainTex"), 0);

	glUniformMatrix4fv(glGetUniformLocation(depthShaderID, "viewProj"), 1, GL_FALSE, &viewProj[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(depthShaderID, "model"), 1,GL_FALSE, &transMat[0][0]);
	glUniform4fv(glGetUniformLocation(depthShaderID, "clipPlane"), 1, &clipPlane[0]);

	mesh->draw();
}