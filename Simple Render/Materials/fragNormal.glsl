#version 330 core

in vec2 uv;
in mat3 TBN;
in vec3 o_tangent;

out vec4 color;

uniform sampler2D sampler;
uniform sampler2D normalSampler;
uniform vec3 lightDir;

void main()
{
	color = texture2D(sampler, uv);
	if(color.a < 0.5f)
		discard;
	
	vec3 normal = texture2D(normalSampler, uv).xyz * 2 - 1;
	normal = TBN * normal;
	
	color = color * (max(0.3f, dot(lightDir, normal)));
}