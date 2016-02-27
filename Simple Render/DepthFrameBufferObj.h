#include "stdafx.h"

class DepthFrameBufferObj : public FrameBufferObject
{
	public:
		DepthFrameBufferObj(GLsizei width, GLsizei height);

	protected:
		void genTexture(GLsizei width, GLsizei height);
};