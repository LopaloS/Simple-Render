#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

uniform mat4 viewProj;
uniform mat4 model;
uniform mat4 lightSpace;

out vec2 uv;
out vec2 maskUV;
out mat3 TBN;
out vec3 fragWorldPos;
out vec3 fragLightSpace;

float tiling = 20;

void main()
{
	mat4 mvp = viewProj * model;
	
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	gl_Position = mvp * gl_Position;
	uv = vertexUV * tiling;
	maskUV = vertexUV;
	
	mat3 normModel = mat3(model);
	vec3 N = normModel * normal;
	vec3 T = normModel * tangent;
	vec3 B = cross(N,T);
	TBN = mat3(T,B,N);
	
	fragWorldPos = vec3(model * vec4(vertPos,1));
	fragLightSpace = vec3(lightSpace * vec4(fragWorldPos, 1));
}