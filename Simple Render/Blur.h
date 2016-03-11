#include "stdafx.h"

class Blur
{
public:
	Blur(GLuint iterations, GLsizei screenWidth, GLsizei screenHeight, Mesh* quad);
	GLuint process(GLuint textureID);

private:
	GLuint iterations;
	GLsizei screenWidth, screenHeight;
	Mesh* quad;
	GLuint shaderID;
	vector<FrameBufferObject*> pingPongFBO;
};