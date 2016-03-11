#include "stdafx.h"

Blur::Blur(GLuint iterations, GLsizei screenWidth, GLsizei screenHeight, Mesh* quad)
{
	this->iterations = iterations;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->quad = quad;

	pingPongFBO.push_back(new ColorFrameBufferObj(screenWidth, screenHeight));
	pingPongFBO.push_back(new ColorFrameBufferObj(screenWidth, screenHeight));

	shaderID = ImageMaterial("Blur.glsl").getID();
}

GLuint Blur::process(GLuint textureID) 
{
	bool horizontal = true;
	FrameBufferObject* currentFBO = NULL;

	glUseProgram(shaderID);
	for (int i = 0; i < iterations * 2; i++)
	{
		currentFBO = pingPongFBO[horizontal];
		currentFBO->activate();
		glUniform1i(glGetUniformLocation(shaderID, "horizontal"), horizontal);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glUniform1i(glGetUniformLocation(shaderID, "colorTex"), 0);
		quad->draw();

		textureID = currentFBO->getTextureID();
		horizontal = !horizontal;
	}

	return textureID;
}