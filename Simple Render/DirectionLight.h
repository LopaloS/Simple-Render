#include "stdafx.h"

class DirectionLight
{
	public:
		DirectionLight(GLuint shadowMapID);
		void updatePosition();
		mat4 getLightSpace();
		vec3 getDirection();
		GLuint getShadowMapID();
	private:
		vec3 direction;
		GLuint shadowMapID;
};
