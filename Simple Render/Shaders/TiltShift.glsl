#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D colorTex;
uniform sampler2D bluredTex;
uniform const float blurArea = 1.7;
uniform const float blurSize = 6;
uniform const int discSamples = 28;
const vec2 gaussKernel[28] = vec2[28]
	(
		vec2(0.62463,0.54337),
		vec2(-0.13414,-0.94488),
		vec2(0.38772,-0.43475),
		vec2(0.12126,-0.19282),
		vec2(-0.20388,0.11133),
		vec2(0.83114,-0.29218),
		vec2(0.10759,-0.57839),
		vec2(0.28285,0.79036),
		vec2(-0.36622,0.39516),
		vec2(0.75591,0.21916),
		vec2(-0.52610,0.02386),
		vec2(-0.88216,-0.24471),
		vec2(-0.48888,-0.29330),
		vec2(0.44014,-0.08558),
		vec2(0.21179,0.51373),
		vec2(0.05483,0.95701),
		vec2(-0.59001,-0.70509),
		vec2(-0.80065,0.24631),
		vec2(-0.19424,-0.18402),
		vec2(-0.43667,0.76751),
		vec2(0.21666,0.11602),
		vec2(0.15696,-0.85600),
		vec2(-0.75821,0.58363),
		vec2(0.99284,-0.02904),
		vec2(-0.22234,-0.57907),
		vec2(0.55052,-0.66984),
		vec2(0.46431,0.28115),
		vec2(-0.07214,0.60554)
	);	

void main()
{
	float weight = abs(uv.y * 2 - 1) * blurArea;	
	vec2 texOffset = 1.0 / textureSize(colorTex, 0) * weight * blurSize;
	
	hdrColor = vec3(0);
	for(int i = 0; i < discSamples; i++)
	{
		hdrColor += texture(colorTex, uv + gaussKernel[i] * texOffset).rgb;
	}
	hdrColor /= discSamples;
}