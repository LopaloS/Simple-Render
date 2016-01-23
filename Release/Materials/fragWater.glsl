#version 330 core

in vec2 uv1;
in vec2 uv2;
in mat3 TBN;
in vec3 fragWorldPos;
in vec4 fragDevicePos;

out vec4 color;

uniform sampler2D normalTex;
uniform sampler2D dudvTex;
uniform sampler2D refractionMap;
uniform sampler2D reflectionMap;
uniform vec3 lightDir;
uniform vec3 viewPos;

vec4 waterColor = vec4(0.25f,0.59f,0.62f,1);
float distortion = 0.001f;

void main()
{	
	vec3 normal1 = texture2D(normalTex, uv1).xyz * 2 - 1;
	vec3 normal2 = texture2D(normalTex, uv2).xyz * 2 - 1;
	
	vec2 uvOffset1 = texture2D(dudvTex, uv1).rg * 2 - 1;
	vec2 uvOffset2 = texture2D(dudvTex, uv2).rg * 2 - 1;
	
	vec2 uvOffset = uvOffset1 + uvOffset2;
	uvOffset *= distortion;
	
	vec3 normal = TBN * normalize(normal1 + normal2);
	vec3 viewDir = normalize(viewPos - fragWorldPos);
	
	
	vec2 fragScreenPos = fragDevicePos.xy / fragDevicePos.w;
	fragScreenPos += uvOffset;
	fragScreenPos = fragScreenPos / 2 + 0.5f;
	
	fragScreenPos = clamp(fragScreenPos, vec2(0.001,0.001), vec2(0.999,0.999));
	
	vec4 refrColor = texture2D(refractionMap, fragScreenPos);
	fragScreenPos.y = 1 - fragScreenPos.y;
	vec4 reflColor = texture2D(reflectionMap, fragScreenPos);
	
	float fresnelTerm = max(1 - dot(viewDir, normal) * 1.3f, 0);
	color = mix(waterColor, mix(refrColor, reflColor, fresnelTerm), 0.9f);
	
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float spec = pow((max(0.0f, dot(normal, halfWayDir))), 32);
	vec3 specular = color.rgb * spec;
	
	color.rgb = color.rgb + specular;
}