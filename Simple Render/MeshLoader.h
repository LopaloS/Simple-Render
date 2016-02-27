#include "stdafx.h"

class MeshLoader
{
	public:
		Mesh* loadMesh(string);
	private:
		Mesh* loadMeshObj(string);
	};


