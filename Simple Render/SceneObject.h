#include "stdafx.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, bool solid,GLuint shaderID, map<string, GLuint> texures, mat4 transMat);
	void render(Camera camera, DirectionLight light);
	void renderDepth(GLuint depthShaderID, DirectionLight light);

private:
	Mesh* mesh;
	bool solid;
	GLuint shaderID;
	map<string, GLuint> texures;
	mat4 transMat;
};
