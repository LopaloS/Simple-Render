#version 330 core

in vec2 uv;
in mat3 TBN;
in vec3 vertWorldPos;
in vec3 fragLightSpace;

out vec4 color;

uniform sampler2D sampler;
uniform sampler2D shadowSampler;
uniform sampler2D normalSampler;
uniform vec3 lightDir;
uniform vec3 viewPos;

float getShadow(vec3 normal)
{
	vec3 fragLightSpace = fragLightSpace / 2 + 0.5f; 
	if(fragLightSpace.z > 1.0f)
		return 1;
		
	float bias = max(0.01f * (1.0f - dot(lightDir, normal)), 0.001f);
	vec2 texelSize = 1.0f / textureSize(shadowSampler, 0);
	float shadowFactor = 0.0f;
	
	for(int i = -2; i <= 2; i++)
	{
		for(int j = -2; j <= 2; j++)
		{
			float depth = texture2D(shadowSampler, fragLightSpace.xy + texelSize * vec2(i,j)).r;
			shadowFactor += depth > fragLightSpace.z - bias ? 1:0;
		}
	}
	
	return shadowFactor /= 25;
}

void main()
{
	color = texture2D(sampler, uv);
	if(color.a < 0.5f)
		discard;
	
	vec3 normal = texture2D(normalSampler, uv).xyz * 2 - 1;
	normal = TBN * normal;
	
	vec3 ambient = color.rgb * 0.4f;
	vec3 diffuse = color.rgb * (max(0.0, dot(lightDir, normal)));
	
	vec3 viewDir = normalize(viewPos - vertWorldPos);
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float spec = pow((max(0.0f, dot(normal, halfWayDir))), 16);
	vec3 specular = color.rgb * spec;
	
	color.rgb = ambient + (diffuse + specular) * getShadow(normal);
}