#include "stdafx.h"
//#include <GL/glew.h>
#include <glfw3.h>
#include "common.hpp"
#include "Camera.h";
#include "gtc\matrix_transform.hpp"
#include "Scene.h"

using namespace glm;

#define windowWidth 1280
#define windowHeight 720

GLFWwindow* window;

int main(void)
{
	if(!glfwInit())
		return -1;

	window = glfwCreateWindow(windowWidth, windowHeight, "Simple Render", NULL, NULL);
	glfwMakeContextCurrent(window);

	if( window == NULL )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	
	//glewExperimental = GL_TRUE; 
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); 
	//glEnable(GL_CULL_FACE);

	glClearColor(0.4f,0.5f,1.0f,1.0f);

	Scene* scene = new Scene("Scene.json"); 
	
	Camera camera(window, (float)windowWidth/windowHeight, vec2(windowWidth/2, windowHeight/2));

	while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene->render(camera.getViewMatrix(), camera.getProjMatrix(), camera.getPosition());
		
		camera.update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

