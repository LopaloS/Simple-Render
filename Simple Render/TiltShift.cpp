#include "stdafx.h"

TiltShift::TiltShift(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad) 
	: ImageEffect(screenWidth, screenHeight, quad, ImageMaterial("TiltShift.glsl").getID())
{
	screenWidth *= sizeOfScreen;
	screenHeight *= sizeOfScreen;

	blur = new Blur(2, screenWidth, screenHeight, quad);
}

void TiltShift::process(map<string, GLuint> inTextures) 
{
	glViewport(0, 0, screenWidth * sizeOfScreen, screenHeight * sizeOfScreen);
	inTextures["bluredTex"] = blur->process(inTextures["colorTex"]);
	glViewport(0, 0, screenWidth, screenHeight);

	ImageEffect::process(inTextures);
}