#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D colorTex;

void main()
{
	hdrColor = texture(colorTex, uv).rgb;
	if(dot(hdrColor, vec3(0.2126, 0.7152, 0.0722)) < 1)
		hdrColor = vec3(0);
}