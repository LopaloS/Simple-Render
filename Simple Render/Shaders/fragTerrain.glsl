#version 330 core

in vec2 uv;
in vec2 maskUV;
in mat3 TBN;

out vec4 color;

uniform sampler2D grassTex;
uniform sampler2D dirtTex;
uniform sampler2D brickTex;
uniform sampler2D brickNormalTex;
uniform sampler2D brickSpecularTex;
uniform sampler2D maskTex;

void calcBlinnPhongLight(vec3 normal, float shine);

void main()
{
	vec4 grassColor = texture2D(grassTex, uv);
	vec4 dirtColor = texture2D(dirtTex, uv);
	vec4 brickColor = texture2D(brickTex, uv);
	vec4 maskColor = texture2D(maskTex, maskUV);
	
	color = mix(grassColor, dirtColor, maskColor.r);
	color = mix(color, brickColor, maskColor.g);
	
	vec3 normal = texture2D(brickNormalTex, uv).xyz * 2 - 1;
	normal = mix(vec3(0,0,1), normal, maskColor.g);
	normal = TBN * normal;
	
	float shine = texture2D(brickSpecularTex, uv).r;
	shine = mix(shine, 1, maskColor.g);
	
	calcBlinnPhongLight(normal, shine);
}