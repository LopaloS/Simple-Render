#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertexUV;

uniform mat4 viewProj;
uniform mat4 model;

out vec2 uv;

void main()
{
	mat4 mvp = viewProj * model;
	
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	gl_Position = mvp * gl_Position;
	uv = vertexUV;
}