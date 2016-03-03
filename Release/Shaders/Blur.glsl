#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D colorTex;
uniform bool horizontal;
uniform float weight[16] = float[] (0.132368, 0.125279,	0.106209, 0.080656,	0.054865, 0.033431,	0.018246, 0.00892, 0.003906, 0.001532, 0.000538, 0.000169, 0.000048, 0.000012, 0.000003, 0.000001);					   

void main()
{
	vec2 texOffset = 1.0 / textureSize(colorTex, 0);
	hdrColor = texture2D(colorTex, uv).rgb * weight[0];
	vec2 dir = horizontal ? vec2(1,0) : vec2(0,1);
	
	vec2 offset;
	for(int i = 1; i < 15; i++)
	{
		offset = dir * i * texOffset;
		hdrColor += texture(colorTex, uv + offset).rgb * weight[i];
		hdrColor += texture(colorTex, uv - offset).rgb * weight[i];
	}
}


