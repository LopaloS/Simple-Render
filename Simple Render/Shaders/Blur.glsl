#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D colorTex;
uniform bool horizontal;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);						   

void main()
{
	vec2 texOffset = 1.0 / textureSize(colorTex, 0);
	hdrColor = texture2D(colorTex, uv).rgb * weight[0];
	vec2 dir = horizontal ? vec2(1,0) : vec2(0,1);
	
	vec2 offset;
	for(int i = 1; i < 5; i++)
	{
		offset = dir * i * texOffset;
		hdrColor += texture(colorTex, uv + offset).rgb * weight[i];
		hdrColor += texture(colorTex, uv - offset).rgb * weight[i];
	}
}


