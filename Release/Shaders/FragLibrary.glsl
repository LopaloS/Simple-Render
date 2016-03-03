#version 330 core

in vec3 fragWorldPos;
in vec3 fragLightSpace;

out vec4 color;

uniform float near = 0.3; 
uniform float far  = 1000.0; 
uniform sampler2D shadowMap;
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

void calcBlinnPhongLight(vec3 normal, float shine)
{
	vec3 ambient = color.rgb * 0.4f;
	vec3 diffuse = color.rgb * (max(0.0, dot(lightDir, normal)));
	
	vec3 viewDir = normalize(viewPos - fragWorldPos);
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float spec = pow((max(0.0f, dot(normal, halfWayDir))), shine * 16);
	vec3 specular = color.rgb * spec;
	
	color.rgb = ambient + (diffuse + specular) * getShadow();
}

float linearizeDepth(float depth) 
{
	return (2.0 * near * far) / (far + near - depth * (far - near));
}
