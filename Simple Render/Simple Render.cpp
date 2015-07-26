
#include "stdafx.h"
#include <GL/glew.h>
#include <glfw3.h>
#include "MeshLoader.h"
#include "Material.h"
#include "common.hpp"
#include "Camera.h";
#include "gtc\matrix_transform.hpp"

using namespace glm;

#define windowWidth 1024
#define windowHeight 768

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
	glEnable(GL_CULL_FACE);

	glClearColor(0.4f,0.5f,1.0f,1.0f);

	MeshLoader* meshLoader = new MeshLoader();
	Mesh* mesh = meshLoader->loadMesh("Axe1.obj");
	Material material("Shader.glsl", "Woodcutter-Axe.jpg");

	GLuint textureSamplerID = glGetUniformLocation(material.getShaderID(), "texture");
	GLuint mvpMatrixID = glGetUniformLocation(material.getShaderID(), "mvp");
	Camera camera(window, (float)windowWidth/windowHeight, vec2(windowWidth/2, windowHeight/2));
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);



	while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(material.getShaderID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material.getTextureID());
		glUniform1d(textureSamplerID, 0);
		glUniformMatrix4fv(mvpMatrixID, 1,GL_FALSE, &camera.GetViewProjMatrix()[0][0]);

		if(mesh)
			mesh->render();
		camera.Update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

