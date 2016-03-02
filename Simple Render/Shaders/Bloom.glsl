#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D brightnessTex;
uniform sampler2D colorTex;


void main()
{
	vec3 brightness = texture(brightnessTex, uv).rgb;
	hdrColor = texture(colorTex, uv).rgb;
	//hdrColor += brightness;
}