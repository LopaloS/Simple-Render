#version 330 core

in vec2 uv;
in mat3 TBN;
in vec3 vertWorldPos;

out vec4 color;

uniform sampler2D mainTex;
uniform sampler2D normalTex;
uniform sampler2D specularTex;

float getShadow();
void calcBlinnPhongLight(vec3 normal, float shine);

void main()
{
	color = texture2D(mainTex, uv);
	if(color.a < 0.5f)
		discard;
	
	vec3 normal = texture2D(normalTex, uv).xyz * 2 - 1;
	normal = TBN * normal;
	
	float shine = texture2D(specularTex, uv).r;
	calcBlinnPhongLight(normal, shine);
}