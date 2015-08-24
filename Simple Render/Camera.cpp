#include "stdafx.h"
#include "Camera.h"
#include <gtx/transform.hpp>

Camera::Camera(GLFWwindow* window, float aspectRatio, vec2 screenCenter)
{
	this->window = window;
	this->screenCenter = screenCenter;
	this->aspectRatio = aspectRatio;
	speed = 5;
	fov = 55;
	position = vec3(0,0, -10);
	mouseSens = 0.001;
}

void Camera::Update()
{

	double curTime = glfwGetTime();
	float deltaTime = lastTime - curTime;
	lastTime = curTime;

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, screenCenter.x, screenCenter.y);

	rotation.y -= (screenCenter.x - xpos) * mouseSens;
	rotation.x += (screenCenter.y - ypos) * mouseSens;

	rotation.x = clamp(rotation.x, -1.57f, 1.57f); // radians

	mat4 rotMat =  rotate(rotation.y, vec3(0,1,0)) * rotate(rotation.x, vec3(1,0,0));
	vec3 forwardDirection = (vec3)(rotMat * vec4(0,0,1,0));

	vec3 rightDirection = cross(forwardDirection, vec3(0,1,0));
	normalize(rightDirection);

	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		position -= forwardDirection * speed * deltaTime;
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		position += forwardDirection * speed * deltaTime;
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		position -= rightDirection * speed * deltaTime;
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		position += rightDirection * speed * deltaTime;

	mat4 projectionMat = perspective(fov, aspectRatio, 0.1f, 100.0f);
	mat4 viewMat = lookAt(position, position + forwardDirection, vec3(0,1,0));
	viewProjMatrix = projectionMat * viewMat;
}

mat4 Camera::GetViewProjMatrix()
{
	return viewProjMatrix;
}