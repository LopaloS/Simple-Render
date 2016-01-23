#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

uniform mat4 viewProj;
uniform mat4 model;
uniform float time;

out vec2 uv1;
out vec2 uv2;
out mat3 TBN;
out vec3 fragWorldPos;
out vec4 fragDevicePos;

vec2 tileSpeed = vec2(0.003f, 0.003f);
vec2 tileScale = vec2(15f,15f);

void main()
{
	mat4 mvp = viewProj * model;
	gl_Position.xyz = vertPos;
	gl_Position.y = 0;
	gl_Position.w = 1;
	gl_Position = mvp * gl_Position;
	fragDevicePos = gl_Position;
	uv1 = vec2(vertexUV.x, vertexUV.y + time * tileSpeed.y + 0.43f) * tileScale.x;
	uv2 = vec2(vertexUV.x + time * tileSpeed.x, vertexUV.y) * tileScale.y;
	
	mat3 normModel = mat3(model);
	vec3 N = normModel * normal;
	vec3 T = normModel * tangent;
	
	vec3 B = cross(N,T);
	
	TBN = mat3(T,B,N);
	fragWorldPos = vec3(model * vec4(vertPos, 1));
}