#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh()
{
	
}

Mesh::Mesh(vector<float>* verts, vector<GLuint>* indeces, vector<float>* uvs, vector<float>* normals)
{
	if(verts)
	{
		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), &verts->at(0), GL_STATIC_DRAW);
	}

	if(uvs)
	{
		glGenBuffers(1, &uvBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glBufferData(GL_ARRAY_BUFFER, uvs->size() * sizeof(float), &uvs->at(0), GL_STATIC_DRAW);
	}

	if(indeces)
	{
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeces->size() * sizeof(GLuint), &indeces->at(0), GL_STATIC_DRAW);
		indexBufferSize = indeces->size();
	}
}

void Mesh::render()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	//glDrawElements(GL_TRIANGLES, indexBufferSize, GL_UNSIGNED_INT, NULL);
	glDrawArrays(GL_TRIANGLES, 0, indexBufferSize);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}