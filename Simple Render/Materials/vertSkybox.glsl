#version 330 core

layout(location = 0) in vec3 vertPos;

uniform mat4 mvp;

out vec3 uv;

void main()
{
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	gl_Position = mvp * gl_Position;
	gl_Position = gl_Position.xyww;
	uv = vertPos;
}