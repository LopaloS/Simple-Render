#version 330 core

in vec3 uv;
out vec4 color;

uniform samplerCube sampler;

void main()
{
	color = texture(sampler, uv);
}