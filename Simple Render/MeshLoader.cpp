#include "MeshLoader.h"
#include <vector>
using namespace std;

Mesh* MeshLoader::loadMesh(char* name)
{
	return loadMeshObj(name);
}

Mesh* MeshLoader::loadMeshObj(char* name)
{
	FILE* file = fopen(name, "r");

	if (!file)
	{
		printf("File does not exist");
		return NULL;
	}

	vector<GLuint>* vertIndeces = new vector<GLuint>();
	vector<float> tempVerts;
	vector<float> tempUVs;
	
	
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
			float x,y,z;
			fscanf(file, "%f %f %f", &x, &y, &z);

			tempVerts.push_back(x * 0.2f);
			tempVerts.push_back(y * 0.2f);
			tempVerts.push_back(z * 0.2f);
		}

		if (strcmp(line, "vt") == 0)
		{
			float u,v;
			fscanf(file, "%f %f",&u, &v);

			tempUVs.push_back(u);
			tempUVs.push_back(v);
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
	
	vector<float>* verts = new vector<float>();
	vector<float>* UVs = new vector<float>();
	for (int i = 0; i < vertIndeces->size(); i++)
	{
		GLuint vertexIndex = vertIndeces->at(i);
		verts->push_back(tempVerts[vertexIndex * 3]);
		verts->push_back(tempVerts[vertexIndex * 3 + 1]);
		verts->push_back(tempVerts[vertexIndex * 3 + 2]);

		GLuint uvIndex = uvIndeces[i];
		UVs->push_back(tempUVs[uvIndex * 2]);
		UVs->push_back(tempUVs[uvIndex * 2 + 1]);
	}

	return new Mesh(verts, vertIndeces, UVs);
}

