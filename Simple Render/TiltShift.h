#include "stdafx.h"

class TiltShift : public ImageEffect
{
public:
	TiltShift(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad);
	void process(map<string, GLuint> inTextures);

private:
	const float sizeOfScreen = 1;
	Blur* blur;
};
