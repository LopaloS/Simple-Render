#include "stdafx.h"

class FrameBufferObject
{
	public:
		FrameBufferObject(GLsizei width, GLsizei height, bool color);
		GLuint getTextureID();
		void activate();

	private:
		bool color;
		GLuint frameBufferID;
		GLuint textureID;

		void genTexture(GLsizei width, GLsizei height, bool color);
};