#include "stdafx.h"

class Texture
{
	public:
		Texture(string);
		GLuint getID();
	private:
		GLuint id;
};