#version 330 core

in vec2 uv;
in vec3 oNormal;
in vec3 vertWorldPos;
in vec3 fragLightSpace;

out vec4 color;

uniform sampler2D sampler;
uniform sampler2D shadowSampler;

uniform vec3 lightDir;
uniform vec3 viewPos;

float getShadow()
{
	vec3 fragLightSpace = fragLightSpace / 2 + 0.5f; 
	float depth = texture2D(shadowSampler, fragLightSpace.xy).r;
	if(fragLightSpace.z > 1.0f)
		return 1;
	float bias = max(0.005f * (1.0f - dot(lightDir, oNormal)), 0.0005f);
	return depth > fragLightSpace.z - bias ? 1:0;
}

void main()
{
	color = texture2D(sampler, uv);
	if(color.a < 0.5f)
		discard;
		
	vec3 ambient = color.rgb * 0.2f;
	vec3 diffuse = color.rgb * (max(0.0, dot(lightDir, oNormal)));
	
	vec3 viewDir = normalize(viewPos - vertWorldPos);
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float spec = pow((max(0.0f, dot(oNormal, halfWayDir))), 16);
	vec3 specular = color.rgb * spec;
	
	color.rgb = ambient + (diffuse + specular) * getShadow();
}