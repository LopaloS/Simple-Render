#include "stdafx.h"

class Bloom : public ImageEffect
{
	public:
		Bloom(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad);
		void process(map<string, GLuint> inTextures);

	private:
		const float sizeOfScreen = 0.5;
		const int iterations = 10;
		GLuint brightnessShaderID;
		GLuint blurShaderID;
		vector<FrameBufferObject*> pingPongFBO;
};