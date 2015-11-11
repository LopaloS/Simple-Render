#version 330 core

in vec2 uv;
in vec3 oNormal;
in vec3 vertWorldPos;

out vec4 color;

uniform sampler2D sampler;
uniform vec3 lightDir;
uniform vec3 viewPos;

void main()
{
	color = texture2D(sampler, uv);
	if(color.a < 0.5f)
		discard;
		
	vec3 ambient = color.rgb * 0.5f;
	vec3 diffuse = color.rgb * (max(0.0, dot(lightDir, oNormal)));
	
	vec3 viewDir = normalize(viewPos - vertWorldPos);
	vec3 halfWayDir = normalize(viewDir + lightDir);
	float spec = pow((max(0.0f, dot(oNormal, halfWayDir))), 32);
	vec3 specular = color.rgb * spec;
	
	color.rgb = ambient + diffuse + specular;
}