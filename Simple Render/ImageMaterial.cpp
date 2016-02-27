#include "stdafx.h"

ImageMaterial::ImageMaterial(string shaderName) 
{
	GLuint vertexShaderID = loadShader("vertImage.glsl", GL_VERTEX_SHADER);
	GLuint fragmentShaderID = loadShader(shaderName.c_str(), GL_FRAGMENT_SHADER);
	linkProgram(vertexShaderID, fragmentShaderID);
}


