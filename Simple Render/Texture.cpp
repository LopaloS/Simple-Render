#include "stdafx.h"

Texture::Texture(){};

Texture::Texture(string name)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, load(name));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

BYTE* Texture::load(string name)
{
	FIBITMAP* bitMap = NULL;

	string folder("Textures/");
	bitMap = FreeImage_Load(FIF_PNG, (folder + name).c_str());
	bitMap = FreeImage_ConvertTo32Bits(bitMap);
	width = FreeImage_GetWidth(bitMap);
	height = FreeImage_GetHeight(bitMap);
	return FreeImage_GetBits(bitMap);
}

GLuint Texture::getID()
{
	return id;
}