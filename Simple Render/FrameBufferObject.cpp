#include "stdafx.h"

FrameBufferObject::FrameBufferObject(GLsizei width, GLsizei height)
{
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
}

GLuint FrameBufferObject::getTextureID()
{
	return textureID;
}

void FrameBufferObject::activate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBufferObject::genTexture(GLsizei width, GLsizei height) 
{
	glGenTextures(1, &textureID);	
	glBindTexture(GL_TEXTURE_2D, textureID);	
}