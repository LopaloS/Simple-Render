#include "stdafx.h"

ImageEffect::ImageEffect(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad, GLuint shaderID)
{
	this->screenWidth = screenWidth; 
	this->screenHeight = screenHeight;
	this->quad = quad;
	this->shaderID = shaderID;
	imageEffect = NULL;
	colorFBO = NULL;
}

void ImageEffect::setImageEffect(ImageEffect* imageEffect = NULL)
{
	this->imageEffect = imageEffect;
	if(colorFBO == NULL)
		colorFBO = new ColorFrameBufferObj(screenWidth, screenHeight);
}

void ImageEffect::process(map<string, GLuint> inTextures)
{
	if(imageEffect == NULL)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	else
		colorFBO->activate();

	glUseProgram(shaderID);
	draw(shaderID, inTextures);

	if(imageEffect != NULL)
	{
		inTextures["colorTex"] = colorFBO->getTextureID();
		imageEffect->process(inTextures);
	}
}

void ImageEffect::activateTextures(GLuint shaderID, map<string, GLuint> inTextures)
{
	GLuint curTexture = GL_TEXTURE0;
	GLuint uniformLocation = 0;

	for (auto iter = inTextures.begin(); iter != inTextures.end(); iter++)
	{
		glActiveTexture(curTexture);
		glBindTexture(GL_TEXTURE_2D, iter->second);
		glUniform1i(glGetUniformLocation(shaderID, iter->first.c_str()), uniformLocation);
		curTexture++;
		uniformLocation++;
	}
}

void ImageEffect::draw(GLuint shaderID, map<string, GLuint> inTextures)
{
	activateTextures(shaderID, inTextures);
	quad->draw();
}