#include "stdafx.h"
#include <vector>
#include "glm.hpp"

using namespace glm;
using namespace std;

class Mesh
{
	public:
		Mesh();
		Mesh(vector<vec3>* verts, vector<vec2>* uvs = NULL, vector<vec3>* normals = NULL);

		void draw();
	private:
		
		GLuint vertexCount;

		GLuint vertexBufferID;
		GLuint uvBufferID;
		GLuint normalBufferID;
		GLuint tangentBufferID;

		void calcTangents(vector<vec3>* verts, vector<vec2>* uvs);
};
