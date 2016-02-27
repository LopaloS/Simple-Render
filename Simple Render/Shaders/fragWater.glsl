#version 330 core

in vec2 uv1;
in vec2 uv2;
in mat3 TBN;
in vec3 fragWorldPos;
in vec4 fragDevicePos;

out vec4 color;

uniform sampler2D normalTex;
uniform sampler2D refractionMap;
uniform sampler2D depthMap;
uniform sampler2D reflectionMap;
uniform vec3 lightDir;
uniform vec3 viewPos;

vec4 waterColor = vec4(0f,0.1f,0.1f,1);
float distortion = 0.1f;


float near = 0.3; 
float far  = 1000.0; 

float linearizeDepth(float depth) 
{
	return (2.0 * near * far) / (far + near - depth * (far - near));
}

void main()
{	
	vec3 normal1 = texture2D(normalTex, uv1).xyz * 2 - 1;
	vec3 normal2 = texture2D(normalTex, uv2).xyz * 2 - 1;
	
	vec3 tangentSpaceNormal = normalize(normal1 + normal2);
	vec3 normal = TBN * tangentSpaceNormal;
	
	vec3 viewDir = normalize(viewPos - fragWorldPos);
	
	vec2 uvOffset = tangentSpaceNormal.xy;
	uvOffset *= distortion;
	
	vec2 fragScreenPos = fragDevicePos.xy / fragDevicePos.w;
	
	
	fragScreenPos = fragScreenPos / 2 + 0.5f;
	
	
	float waterDepth = gl_FragCoord.z;
	waterDepth = linearizeDepth(waterDepth);;
	float underwaterDepth = texture2D(depthMap, fragScreenPos).r;
	underwaterDepth = linearizeDepth(underwaterDepth);
	underwaterDepth -= waterDepth;
	underwaterDepth /= 15;
	uvOffset *= underwaterDepth;
	
	fragScreenPos += uvOffset;
	fragScreenPos = clamp(fragScreenPos, 0.001, 0.999);
	
	vec4 refrColor = texture2D(refractionMap, fragScreenPos);
	fragScreenPos.y = 1 - fragScreenPos.y;
	vec4 reflColor = texture2D(reflectionMap, fragScreenPos);
	
	float fresnelTerm = max(1 - dot(viewDir, normal) * 1.3f, 0);
	color = mix(refrColor, reflColor, fresnelTerm);
	color = mix(color, waterColor,clamp(underwaterDepth, 0,0.6));
	
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float spec = pow((max(0.0f, dot(normal, halfWayDir))), 32);
	vec3 specular = color.rgb * spec;
	
	color.rgb = color.rgb + specular;
	color.a = underwaterDepth;
}