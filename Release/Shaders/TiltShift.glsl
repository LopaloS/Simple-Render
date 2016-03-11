#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D colorTex;
uniform sampler2D bluredTex;
uniform float blurArea = 1.7;

void main()
{
	float lerpValue = clamp(abs(uv.y * 2 - 1) * blurArea,0,1);
	hdrColor = texture(colorTex, uv).rgb;
	vec3 bluredColor = texture(bluredTex, uv).rgb;
	hdrColor = mix(hdrColor, bluredColor, lerpValue);
}