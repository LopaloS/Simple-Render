#include "stdafx.h"

class DirectionLight
{
	public:
		void updatePosition();
		mat4 getLightSpace();
		vec3 getDirection();
	private:
		vec3 direction;
};
