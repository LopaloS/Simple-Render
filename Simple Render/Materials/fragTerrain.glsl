#version 330 core

in vec2 uv;
in vec2 maskUV;
in mat3 TBN;
in vec3 vertWorldPos;
in vec3 fragLightSpace;

out vec4 color;

uniform sampler2D grassTex;
uniform sampler2D dirtTex;
uniform sampler2D brickTex;
uniform sampler2D brickNormalTex;
uniform sampler2D brickSpecularTex;
uniform sampler2D maskTex;
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
	
	vec3 ambient = color.rgb * 0.4f;
	vec3 diffuse = color.rgb * (max(0.0, dot(lightDir, normal)));
	
	vec3 viewDir = normalize(viewPos - vertWorldPos);
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float shine = texture2D(brickSpecularTex, uv).r * 32;
	shine = mix(shine, 32, maskColor.g);
	float spec = pow((max(0.0f, dot(normal, halfWayDir))), shine);
	vec3 specular = color.rgb * spec;
	
	color.rgb = ambient + (diffuse + specular) * getShadow();
}