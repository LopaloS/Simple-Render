

class Material
{
	public:
		Material();
		Material(string);

		GLuint getID();

	protected:
		GLuint loadShader(const char* name, GLenum type);
		void linkProgram(GLuint vert, GLuint frag);

	private:
		static const string folder;
		GLuint id;
		
};
