#include "FrameBufferObject.h"

FrameBufferObject::FrameBufferObject(GLsizei width, GLsizei height, bool color)
{
	this->color = color;
	genTexture(width, height, color);

	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	GLuint atachment = color ? GL_COLOR_ATTACHMENT0 : GL_DEPTH_ATTACHMENT;
	glFramebufferTexture2D(GL_FRAMEBUFFER, atachment, GL_TEXTURE_2D, textureID, 0);

	if(color)
	{
		GLuint renderBufferID;
		glGenRenderbuffers(1, &renderBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID); 
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); 
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferID);
	}
	else
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
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

void FrameBufferObject::genTexture(GLsizei width, GLsizei height, bool color)
{
	glGenTextures(1, &textureID);	
	glBindTexture(GL_TEXTURE_2D, textureID);

	GLenum format = color ? GL_RGB : GL_DEPTH_COMPONENT;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,0, format, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); 
}