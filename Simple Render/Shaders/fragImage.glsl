#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D colorTex;

void main()
{
	hdrColor = texture2D(colorTex, uv).rgb;
}