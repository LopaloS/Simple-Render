#version 330 core

in vec2 uv1;
in vec2 uv2;
in mat3 TBN;
in vec3 fragWorldPos;
in vec3 fragLightSpace;

out vec4 color;

uniform sampler2D shadowMap;
uniform sampler2D normalTex;
uniform samplerCube skybox;
uniform vec3 lightDir;
uniform vec3 viewPos;

float getShadow()
{
	vec3 fragLightSpace = fragLightSpace / 2 + 0.5f; 
	if(fragLightSpace.z > 1.0f)
		return 1;
		
	vec2 texelSize = 1.0f / textureSize(shadowMap, 0);
	float shadowFactor = 0.0f;
	
	for(int i = -2; i <= 2; i++)
	{
		for(int j = -2; j <= 2; j++)
		{
			float depth = texture2D(shadowMap, fragLightSpace.xy + texelSize * vec2(i,j)).r;
			shadowFactor += depth > fragLightSpace.z ? 1:0;
		}
	}
	
	return shadowFactor /= 25;
}

void main()
{	
	vec3 normal1 = texture2D(normalTex, uv1).xyz * 2 - 1;
	vec3 normal2 = texture2D(normalTex, uv2).xyz * 2 - 1;
	
	vec3 normal = TBN * normalize(normal1 + normal2);
	vec3 viewDir = normalize(viewPos - fragWorldPos);
	
	color = vec4(0.15f,0.29f,0.42f,1);
	vec4 reflColor = texture(skybox, refract(viewDir, normal,0.75f));
	float fresnelTerm = max(1 - dot(viewDir, normal) * 1.3f, 0);
	color = mix(color, reflColor, fresnelTerm);
	
	vec3 ambient = color.rgb * 0.4f;
	vec3 diffuse = color.rgb * (max(0.0, dot(lightDir, normal)));
	
	
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float spec = pow((max(0.0f, dot(normal, halfWayDir))), 32);
	vec3 specular = color.rgb * spec;
	
	color.rgb = ambient + (diffuse + specular) * getShadow();
}