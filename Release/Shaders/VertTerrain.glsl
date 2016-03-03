#version 330 core

layout(location = 1) in vec2 vertexUV;

out vec2 uv;
out vec2 maskUV;

float tiling = 20;

void transformVertex();
void calcVariables();
void calcTBN();

void main()
{
	transformVertex();
	calcVariables();
	calcTBN();
	
	uv = vertexUV * tiling;
	maskUV = vertexUV;
}