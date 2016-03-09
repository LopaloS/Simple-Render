#include "stdafx.h"

Bloom::Bloom(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad) 
	: ImageEffect(screenWidth, screenHeight, quad, ImageMaterial("Bloom.glsl").getID())
{
	screenWidth *= sizeOfScreen;
	screenHeight *= sizeOfScreen;

	brightnessShaderID = ImageMaterial("Brightness.glsl").getID();
	blurShaderID = ImageMaterial("Blur.glsl").getID();

	colorFBO = new ColorFrameBufferObj(screenWidth, screenHeight);
	pingPongFBO.push_back(new ColorFrameBufferObj(screenWidth, screenHeight));
	pingPongFBO.push_back(new ColorFrameBufferObj(screenWidth, screenHeight));
}

void Bloom::process(map<string, GLuint> inTextures)
{
	glViewport(0, 0, screenWidth * sizeOfScreen, screenHeight * sizeOfScreen);

	colorFBO->activate();
	glUseProgram(brightnessShaderID);
	draw(brightnessShaderID, inTextures);

	map<string, GLuint> textures;
	textures["colorTex"] = colorFBO->getTextureID();
	
	bool horizontal = true;
	FrameBufferObject* currentFBO = NULL;

	glUseProgram(blurShaderID);
	for (int i = 0; i < iterations; i++)
	{
		currentFBO = pingPongFBO[horizontal];
		currentFBO->activate();
		glUniform1i(glGetUniformLocation(blurShaderID, "horizontal"), horizontal);
		draw(brightnessShaderID, textures);
		inTextures["brightnessTex"] = currentFBO->getTextureID();
		textures["colorTex"] = currentFBO->getTextureID();
		horizontal = !horizontal;
	}

	glViewport(0, 0, screenWidth , screenHeight);
	ImageEffect::process(inTextures);
}
