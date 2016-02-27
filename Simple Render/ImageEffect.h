#include "stdafx.h"

class ImageEffect
{
	public:
		ImageEffect(GLsizei screenWidth, GLsizei screenHeight, Mesh* quad, GLuint shaderID);
		void setImageEffect(ImageEffect* imageEffect);
		virtual void process(map<string, GLuint> inTextures);

	protected:
		GLsizei screenWidth, screenHeight; 
		Mesh* quad;
		GLuint shaderID;
		FrameBufferObject* colorFBO;
		ImageEffect* imageEffect;

		void activateTextures(map<string, GLuint> inTextures);
		void draw(map<string, GLuint> inTextures);
};

