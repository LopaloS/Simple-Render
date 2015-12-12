#version 330 core

layout(location = 0) in vec3 vertPos;

uniform mat4 viewProjModel;

void main()
{
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	gl_Position = viewProjModel * gl_Position;
}