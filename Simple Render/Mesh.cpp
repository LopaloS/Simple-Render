#include "stdafx.h"
#include <gtc/matrix_access.hpp>

Mesh::Mesh()
{
	
}

Mesh::Mesh(vector<vec3>* verts, vector<vec2>* uvs, vector<vec3>* normals)
{
	uvBufferID = 0;
	normalBufferID = 0;
	tangentBufferID = 0;

	if(verts)
	{
		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(vec3), &verts->at(0), GL_STATIC_DRAW);
	}
	
	if(uvs)
	{
		glGenBuffers(1, &uvBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glBufferData(GL_ARRAY_BUFFER, uvs->size() * sizeof(vec2), &uvs->at(0), GL_STATIC_DRAW);
	}

	if(normals)
	{
		glGenBuffers(1, &normalBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glBufferData(GL_ARRAY_BUFFER, normals->size() * sizeof(vec3), &normals->at(0), GL_STATIC_DRAW);
	}

	vertexCount = verts->size();

	if(verts && uvs)
		calcTangents(verts, uvs);
}

void Mesh::calcTangents(vector<vec3>* verts, vector<vec2>* uvs)
{
	vector<vec3> tangents;

	for(int i = 0; i < vertexCount; i+=3)
	{
		vec3 edge0 = verts->at(i + 1) - verts->at(i);
		vec3 edge1 = verts->at(i + 2) - verts->at(i);

		vec2 deltaUV0 = uvs->at(i + 1) - uvs->at(i);
		vec2 deltaUV1 = uvs->at(i + 2) - uvs->at(i);

		float r = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV0.y * deltaUV1.x);
        vec3 tangent = (edge0 * deltaUV1.y   - edge1 * deltaUV0.y) * r;
		tangent = normalize(tangent);

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);
	}

		glGenBuffers(1, &tangentBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBufferID);
		glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(vec3), &tangents[0], GL_STATIC_DRAW);
}

void Mesh::draw()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	if(uvBufferID > 0)
	{
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	if(normalBufferID > 0)
	{
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	if(tangentBufferID > 0)
	{
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBufferID);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}