#include "MeshLoader.h"
#include <vector>
#include "glm.hpp"

using namespace std;
using namespace glm;

Mesh* MeshLoader::loadMesh(string name)
{
	return loadMeshObj(name);
}

Mesh* MeshLoader::loadMeshObj(string name)
{
	FILE* file = fopen(name.c_str(), "r");

	if (!file)
	{
		printf("File does not exist");
		return NULL;
	}

	vector<GLuint>* vertIndeces = new vector<GLuint>();
	vector<vec3> tempVerts;
	vector<vec2> tempUVs;
	
	vector<GLuint> uvIndeces;
	vector<GLuint> normalIndeces;

	while (true)
	{
		char line[128];

		int res = fscanf(file,"%s", line);
		if(res == EOF)
			break;

		if(strcmp(line, "v") == 0)
		{
			vec3 vertex;
			fscanf(file, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
			tempVerts.push_back(vertex);
		}

		if (strcmp(line, "vt") == 0)
		{
			vec2 uv;
			fscanf(file, "%f %f",&uv.x, &uv.y);

			tempUVs.push_back(uv);
		}

		if(strcmp(line, "f") == 0)
		{
			GLuint v1, v2, v3;
			GLuint uv1, uv2, uv3;
			GLuint n1, n2, n3;

			fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u", &v1, &uv1, &n1, &v2, &uv2, &n2, &v3, &uv3, &n3);
			vertIndeces->push_back(v1 - 1);
			vertIndeces->push_back(v2 - 1);
			vertIndeces->push_back(v3 - 1);

			uvIndeces.push_back(uv1 - 1);
			uvIndeces.push_back(uv2 - 1);
			uvIndeces.push_back(uv3 - 1);
		}
	}
	
	vector<vec3>* verts = new vector<vec3>();
	vector<vec2>* UVs = new vector<vec2>();
	for (int i = 0; i < vertIndeces->size(); i++)
	{
		GLuint vertexIndex = vertIndeces->at(i);
		verts->push_back(tempVerts[vertexIndex]);

		GLuint uvIndex = uvIndeces[i];
		UVs->push_back(tempUVs[uvIndex]);
	}

	return new Mesh(verts, vertIndeces, UVs);
}

