#version 330 core

in vec2 uv;
in mat3 TBN;
in vec3 vertWorldPos;
in vec3 fragLightSpace;

out vec4 color;

uniform sampler2D sampler;
uniform sampler2D shadowSampler;
uniform sampler2D normalSampler;
uniform sampler2D specularSampler;

uniform vec3 lightDir;
uniform vec3 viewPos;

float getShadow(vec3 normal)
{
	vec3 fragLightSpace = fragLightSpace / 2 + 0.5f; 
	float depth = texture2D(shadowSampler, fragLightSpace.xy).r;
	if(fragLightSpace.z > 1.0f)
		return 1;
	float bias = max(0.02f * (1.0f - dot(lightDir, normal)), 0.002f);
	return depth > fragLightSpace.z - bias ? 1:0;
}

void main()
{
	color = texture2D(sampler, uv);
	if(color.a < 0.5f)
		discard;
	
	vec3 normal = texture2D(normalSampler, uv).xyz * 2 - 1;
	normal = TBN * normal;
	
	vec3 ambient = color.rgb * 0.2f;
	vec3 diffuse = color.rgb * (max(0.0, dot(lightDir, normal)));
	
	vec3 viewDir = normalize(viewPos - vertWorldPos);
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float shine = texture2D(specularSampler, uv).r;
	float spec = pow((max(0.0f, dot(normal, halfWayDir))), shine);
	vec3 specular = color.rgb * spec;
	
	color.rgb = ambient + (diffuse + specular) * getShadow(normal);
}