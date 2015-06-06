#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertexUV;

out vec2 uv;

void main()
{
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	uv = vertexUV;
}