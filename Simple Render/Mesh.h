#include <GL/glew.h>
#include <vector>
using namespace std;

class Mesh
	{
	public:
		Mesh();
		Mesh(vector<float>* verts, vector<GLuint>* indeces = NULL, vector<float>* uvs = NULL, vector<float>* normals = NULL);

		void render();
	private:
		
		GLuint indexBufferSize;

		GLuint vertexBufferID;
		GLuint uvBufferID;
		GLuint indexBufferID;
	};
