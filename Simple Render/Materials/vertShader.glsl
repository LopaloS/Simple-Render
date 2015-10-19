#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertexUV;

uniform mat4 mvp;

out vec2 uv;

void main()
{
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	gl_Position = mvp * gl_Position;
	uv = vertexUV;
}