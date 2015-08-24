#include "stdafx.h"
#include "string"

class MeshLoader
{
	public:
		Mesh* loadMesh(string);
	private:
		Mesh* loadMeshObj(string);
	};


