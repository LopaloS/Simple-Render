#include "stdafx.h"
#include "string"
#include "Mesh.h"

class MeshLoader
{
	public:
		Mesh* loadMesh(char*);
	private:
		Mesh* loadMeshObj(char*);
	};


