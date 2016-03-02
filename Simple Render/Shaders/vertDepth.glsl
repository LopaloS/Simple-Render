#version 330 core

layout(location = 1) in vec2 vertexUV;

out vec2 uv;

void transformVertex();
void calcVariables();

void main()
{
	transformVertex();
	calcVariables();
	
	uv = vertexUV;
}