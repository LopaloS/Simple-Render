#include "stdafx.h"
#include <gtx/transform.hpp>

Camera::Camera(GLFWwindow* window, float aspectRatio, vec2 screenCenter)
{
	this->window = window;
	this->screenCenter = screenCenter;
	this->aspectRatio = aspectRatio;
	speed = 5;
	fov = 45;
	position = vec3(0, 2, -10);
	mouseSens = 0.001;
}

void Camera::update()
{

	double curTime = glfwGetTime();
	float deltaTime = lastTime - curTime;
	lastTime = curTime;

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, screenCenter.x, screenCenter.y);

	rotation.y += (screenCenter.x - xpos) * mouseSens;
	rotation.x -= (screenCenter.y - ypos) * mouseSens;

	rotation.x = clamp(rotation.x, -1.57f, 1.57f); // radians

	mat4 rotMat =  rotate(rotation.y, vec3(0,1,0)) * rotate(rotation.x, vec3(1,0,0));
	viewDirection = (vec3)(rotMat * vec4(0,0,1,0));

	vec3 rightDirection = cross(viewDirection, vec3(0,1,0));
	normalize(rightDirection);

	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position -= viewDirection * speed * deltaTime;
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position += viewDirection * speed * deltaTime;
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position += rightDirection * speed * deltaTime;
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position -= rightDirection * speed * deltaTime;

	setNormalViewMatrix();
}

void Camera::setReflectedViewMatrix(float height)
{
	float offset = 2 * (height - position.y);
	vec3 reflectedPos = position;
	reflectedPos.y += offset;
	vec3 reflectedViewDirection = reflect( viewDirection, vec3(0,1,0));
	
	viewMatrix =  lookAt(reflectedPos, reflectedPos + reflectedViewDirection, vec3(0,1,0));
}

void Camera::setNormalViewMatrix()
{
	viewMatrix = lookAt(position, position + viewDirection, vec3(0,1,0));
}

mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}

mat4 Camera::getProjMatrix()
{
	return perspective(fov, aspectRatio, 0.3f, 1000.0f);
}

vec3 Camera::getPosition()
{
	return position;
}