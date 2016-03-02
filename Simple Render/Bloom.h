#include "stdafx.h"

class Bloom : public ImageEffect
{
	public:
		Bloom(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad);
		void process(map<string, GLuint> inTextures);

	private:
		int iterations = 10;
		GLuint brightnessShaderID;
		GLuint blurShaderID;
		vector<FrameBufferObject*> pingPongFBO;
};