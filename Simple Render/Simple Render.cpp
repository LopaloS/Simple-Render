#include "stdafx.h"
//#include <GL/glew.h>

#include "common.hpp"
#include "Scene.h"

using namespace glm;

#define windowWidth 1280
#define windowHeight 720
#define depthMapResolution 4096

GLFWwindow* window;

GLuint genDepthMap()
{
	GLuint depthMapID; 
	glGenTextures(1, &depthMapID);	
	glBindTexture(GL_TEXTURE_2D, depthMapID);

	glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT, depthMapResolution, depthMapResolution,0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); 
	return depthMapID;
}

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
	
	Camera camera(window, (float)windowWidth/windowHeight, vec2(windowWidth/2, windowHeight/2));
	
	GLuint depthMapID = genDepthMap();
	DirectionLight dirLight(depthMapID);

	Scene* scene = new Scene("Scene.json"); 

	GLuint frameBufferID;
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapID, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glViewport(0,0, depthMapResolution, depthMapResolution);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
		glClear(GL_DEPTH_BUFFER_BIT);

		scene->renderDepth(dirLight);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0, windowWidth, windowHeight);
		scene->render(camera, dirLight);
		
		camera.update();
		dirLight.updatePosition();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

