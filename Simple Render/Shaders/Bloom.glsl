#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D colorTex;
uniform sampler2D brightnessTex;

void main()
{
	vec3 brightness = texture2D(brightnessTex, uv).rgb;
	hdrColor = texture2D(colorTex, uv).rgb;
	hdrColor += brightness;
}