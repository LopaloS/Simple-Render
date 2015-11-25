#include "stdafx.h"
#include "gtc\matrix_transform.hpp"

DirectionLight::DirectionLight(GLuint shadowMapID)
{
	this->shadowMapID = shadowMapID;
}

void DirectionLight::updatePosition()
{
	float angularSpeed = 0.1f;
	direction = normalize(vec3(sin(glfwGetTime() * angularSpeed),0.8f,cos(glfwGetTime() * angularSpeed)));
	//direction = normalize(vec3(0.5f,0.8f,0.5f));
}

vec3 DirectionLight::getDirection()
{
	return direction;
}

mat4 DirectionLight::getLightSpace()
{
	return ortho(-40.0f,40.0f,-40.0f,40.0f,0.1f, 80.0f) * lookAt(direction * 20.0f, vec3(0),  vec3(0,1,0));
}

GLuint DirectionLight::getShadowMapID()
{
	return shadowMapID;
}