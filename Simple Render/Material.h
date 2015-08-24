#include "stdafx.h"

class Material
{
	public:
		Material();
		Material(string);

		GLuint getID();

	private:
		GLuint id;
		void loadShader(const char*);
};
