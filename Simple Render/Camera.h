#include <glfw3.h>
#include "glm.hpp"

using namespace glm;

class Camera
{
	public:
		Camera(GLFWwindow*,float, vec2);
		void update();
		mat4 getViewMatrix();
		mat4 getProjMatrix();
		vec3 getPosition();

		void setReflectedViewMatrix(float height);
		void setNormalViewMatrix();
	private:
		GLFWwindow* window;
		mat4 viewMatrix;

		vec3 position;
		vec3 viewDirection;
		vec2 rotation;
		double lastTime;
		float speed;
		vec2 screenCenter;
		float fov;
		float aspectRatio;

		float mouseSens;
};
