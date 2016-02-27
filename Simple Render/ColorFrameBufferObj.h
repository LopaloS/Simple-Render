#include "stdafx.h"

class ColorFrameBufferObj : public FrameBufferObject
{
public:
	ColorFrameBufferObj(GLsizei width, GLsizei height);

protected:
	void genTexture(GLsizei width, GLsizei height);
};