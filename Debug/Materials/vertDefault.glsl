#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;

uniform mat4 viewProj;
uniform mat4 model;

out vec2 uv;
out vec3 oNormal;
out vec3 vertWorldPos;

void main()
{
	mat4 mvp = viewProj * model;
	
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	gl_Position = mvp * gl_Position;
	uv = vertexUV;
	oNormal = normal;
	vertWorldPos = vec3(model * vec4(vertPos,1));
}