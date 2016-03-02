#version 330 core

in vec2 uv;
in mat3 TBN;
out vec4 color;

uniform sampler2D mainTex;
uniform sampler2D normalTex;

float getShadow();
void calcBlinnPhongLight(vec3 normal, float shine);

void main()
{
	color = texture2D(mainTex, uv);
	if(color.a < 0.5f)
		discard;
	
	vec3 normal = texture2D(normalTex, uv).xyz * 2 - 1;
	normal = TBN * normal;
	
	calcBlinnPhongLight(normal, 1);
}