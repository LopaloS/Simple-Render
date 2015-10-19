#version 330 core

in vec2 uv;
out vec3 color;

uniform sampler2D texture;

void main()
{
	color = texture2D(texture, uv).rgb;
}