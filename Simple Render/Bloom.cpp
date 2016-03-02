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
	colorFBO->activate();
	glUseProgram(brightnessShaderID);
	draw(inTextures);

	map<string, GLuint> textures;
	textures["colorTex"] = colorFBO->getTextureID();

	glUseProgram(blurShaderID);
	
	int currentFBOIndex = 0;
	bool horizontal = true;
	FrameBufferObject* currentFBO = NULL;
	for (int i = 0; i < iterations; i++)
	{
		currentFBO = pingPongFBO[currentFBOIndex];
		currentFBO->activate();
		glUniform1i(glGetUniformLocation(blurShaderID, "horizontal"), horizontal);
		draw(textures);
		inTextures["brightnessTex"] = currentFBO->getTextureID();
		textures["colorTex"] = currentFBO->getTextureID();
		currentFBOIndex = currentFBOIndex == 0 ? 1 : 0;
		horizontal = !horizontal;
	}
	
	ImageEffect::process(inTextures);
}
