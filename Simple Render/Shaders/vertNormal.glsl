#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

uniform mat4 viewProj;
uniform mat4 model;
uniform mat4 lightSpace;
uniform vec4 clipPlane;

out vec2 uv;
out mat3 TBN;
out vec3 fragWorldPos;
out vec3 fragLightSpace;

void main()
{
	mat4 mvp = viewProj * model;
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	gl_Position = mvp * gl_Position;
	uv = vertexUV;
	
	mat3 normModel = mat3(model);
	vec3 N = normModel * normal;
	vec3 T = normModel * tangent;
	vec3 B = cross(N,T);
	
	TBN = mat3(T,B,N);
	
	fragWorldPos = vec3(model * vec4(vertPos, 1));
	fragLightSpace = vec3(lightSpace * vec4(fragWorldPos, 1));
	gl_ClipDistance[0] = dot(vec4(fragWorldPos,1), clipPlane);
}