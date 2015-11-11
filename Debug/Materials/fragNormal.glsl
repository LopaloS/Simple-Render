#version 330 core

in vec2 uv;
in mat3 TBN;
in vec3 vertWorldPos;

out vec4 color;

uniform sampler2D sampler;
uniform sampler2D normalSampler;
uniform vec3 lightDir;
uniform vec3 viewPos;


void main()
{
	color = texture2D(sampler, uv);
	if(color.a < 0.5f)
		discard;
	
	vec3 normal = texture2D(normalSampler, uv).xyz * 2 - 1;
	normal = TBN * normal;
	
	vec3 ambient = color.rgb * 0.5f;
	vec3 diffuse = color.rgb * (max(0.0, dot(lightDir, normal)));
	
	vec3 viewDir = normalize(viewPos - vertWorldPos);
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float spec = pow((max(0.0f, dot(normal, halfWayDir))), 32);
	vec3 specular = color.rgb * spec;
	
	color.rgb = ambient + diffuse + specular;
}