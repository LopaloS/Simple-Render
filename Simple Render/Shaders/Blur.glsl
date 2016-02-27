#version 330 core

in vec2 uv;
out vec3 hdrColor;

uniform sampler2D colorTex;
uniform mat4 weight = mat4(0.22508352, 0.11098164, 0.01330373, 0.00038771,
                           0.00019117, 0.00655965, 0.05472157, 0.11098164,
                           0.00002292, 0.00078633, 0.00655965, 0.01330373,
                           0.00000067, 0.00002292, 0.00019117, 0.00038771);
vec2 texOffset;						   

void main()
{
	hdrColor = texture2D(colorTex, uv).rgb * weight[0][0];
	texOffset = 1.0 / textureSize(colorTex, 0);
	
	for(int i = 1; i < 4; i++)
	{
		for(int j = 1; j < 4; j++)
		{			
			hdrColor += texture2D(colorTex, uv + texOffset * vec2(i,j)).rgb * weight[i][j];
			hdrColor += texture2D(colorTex, uv + texOffset * vec2(i,-j)).rgb * weight[i][j];
			hdrColor += texture2D(colorTex, uv + texOffset * vec2(-i,-j)).rgb * weight[i][j];
			hdrColor += texture2D(colorTex, uv + texOffset * vec2(-i,j)).rgb * weight[i][j];
		}
	}
}
