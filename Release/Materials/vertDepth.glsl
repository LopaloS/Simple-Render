#version 330 core

layout(location = 0) in vec3 vertPos;

uniform mat4 model;
uniform mat4 viewProj;
uniform vec4 clipPlane;

void main()
{
	mat4 mvp = viewProj * model;
	gl_Position.xyz = vertPos;
	gl_Position.w = 1;
	gl_Position = mvp * gl_Position;
	
	vec3 fragWorldPos = vec3(model * vec4(vertPos,1));
	gl_ClipDistance[0] = dot(vec4(fragWorldPos,1), clipPlane);
}