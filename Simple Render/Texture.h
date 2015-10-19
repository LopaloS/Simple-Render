#include "stdafx.h"

class Texture
{
	public:
		Texture();
		Texture(string name);
		GLuint getID();
	protected:
		GLuint width;
		GLuint height;
		GLuint id;
		BYTE* load(string name);
};