#include "stdafx.h"

Bloom::Bloom(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad) 
	: ImageEffect(screenWidth, screenHeight, quad, ImageMaterial("Bloom.glsl").getID())
{
	brightnessShaderID = ImageMaterial("Brightness.glsl").getID();
	blurShaderID = ImageMaterial("Blur.glsl").getID();

	colorFBO = new ColorFrameBufferObj(screenWidth, screenHeight);
	pingPongFBO.push_back(new ColorFrameBufferObj(screenWidth, screenHeight));
	pingPongFBO.push_back(new ColorFrameBufferObj(screenWidth, screenHeight));
}

void Bloom::process(map<string, GLuint> inTextures)
{
	glUseProgram(brightnessShaderID);
	colorFBO->activate();
	draw(inTextures);
	inTextures.insert(pair<string, GLuint>("brightnessTex", colorFBO->getTextureID()));

	map<string, GLuint> textures;
	textures.insert(pair<string, GLuint>("colorTex", colorFBO->getTextureID()));

	glUseProgram(blurShaderID);
	
	int currentFBOIndex = 0;
	for (int i = 0; i < iterations; i++)
	{
		FrameBufferObject* currentFBO = pingPongFBO[currentFBOIndex];
		currentFBO->activate();
		draw(textures);
		inTextures["brightnessTex"] = currentFBO->getTextureID();
		textures["colorTex"] = currentFBO->getTextureID();
		currentFBOIndex = currentFBOIndex == 0 ? 1 : 0;
	}

	ImageEffect::process(inTextures);
}
