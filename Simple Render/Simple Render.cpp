
#include "stdafx.h"
#include <GL/glew.h>
#include <glfw3.h>
#include "MeshLoader.h"
#include "Material.h"

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

	glClearColor(0,0,1,1);
	MeshLoader* meshLoader = new MeshLoader();
	Mesh* mesh = meshLoader->loadMesh("Axe1.obj");
	Material material("Shader.glsl", "Woodcutter-Axe.jpg");
	GLuint textureSamplerID = glGetUniformLocation(material.getShaderID(), "texture");

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(material.getShaderID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material.getTextureID());
		glUniform1d(textureSamplerID, 0);

		if(mesh)
			mesh->render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

