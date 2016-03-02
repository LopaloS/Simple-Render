#version 330 core

layout(location = 1) in vec2 vertexUV;

out vec2 uv;

void transformVertex();
void calcVariables();
void calcTBN();

void main()
{
	transformVertex();
	calcVariables();
	calcTBN();
	
	uv = vertexUV;
}