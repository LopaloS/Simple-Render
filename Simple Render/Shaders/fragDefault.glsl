#version 330 core

in vec2 uv;
in vec3 oNormal;

out vec4 color;

uniform sampler2D mainTex;

uniform vec3 lightDir;
uniform vec3 viewPos;

float getShadow();
void calcBlinnPhongLight(vec3 normal, float shine);

void main()
{
	color = texture2D(mainTex, uv);
	if(color.a < 0.5f)
		discard;
		
	calcBlinnPhongLight(oNormal, 1);
}