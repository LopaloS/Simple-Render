#version 330 core

layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;

out vec2 uv;
out vec3 oNormal;

void transformVertex();
void calcVariables();

void main()
{
	transformVertex();
	calcVariables();
	
	uv = vertexUV;
	oNormal = normal;
}