#include "stdafx.h"

Bloom::Bloom(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad) 
	: ImageEffect(screenWidth, screenHeight, quad, ImageMaterial("Bloom.glsl").getID())
{
	brightnessShaderID = ImageMaterial("Brightness.glsl").getID();
	colorFBO = new ColorFrameBufferObj(screenWidth, screenHeight);

	screenWidth *= sizeOfScreen;
	screenHeight *= sizeOfScreen;

	blur = new Blur(iterations, screenWidth, screenHeight, quad);
}

void Bloom::process(map<string, GLuint> inTextures)
{
	colorFBO->activate();
	glUseProgram(brightnessShaderID);
	draw(brightnessShaderID, inTextures);

	glViewport(0, 0, screenWidth * sizeOfScreen, screenHeight * sizeOfScreen);
	inTextures["brightnessTex"] = blur->process(colorFBO->getTextureID());
	glViewport(0, 0, screenWidth, screenHeight);

	ImageEffect::process(inTextures);
}
