#include "stdafx.h"

class FrameBufferObject
{
	public:
		GLuint getTextureID();
		void activate();

	protected:
		GLuint textureID;
		FrameBufferObject(GLsizei width, GLsizei height);
		virtual void genTexture(GLsizei width, GLsizei height);
	private:
		GLuint frameBufferID;	
};