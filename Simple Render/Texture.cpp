#include "stdafx.h"
#include "FreeImage.h"

Texture::Texture(string name)
{
	FIBITMAP* bitMap = NULL;
	BYTE* textureData = NULL;

	bitMap = FreeImage_Load(FIF_JPEG, name.c_str());
	textureData = FreeImage_GetBits(bitMap);

	unsigned pixel_size = FreeImage_GetBPP(bitMap);

	GLuint width = FreeImage_GetWidth(bitMap);
	GLuint height = FreeImage_GetHeight(bitMap);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint Texture::getID()
{
	return id;
}