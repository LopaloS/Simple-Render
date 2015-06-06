#include "GL\glew.h"

class Material
	{
	public:
		Material();
		Material(char*, char*);

		GLuint getShaderID();
		GLuint getTextureID();

	private:
		GLuint shaderID;
		GLuint textureID;
		void loadShader(char*);
		void loadTexture(char*);
	};
