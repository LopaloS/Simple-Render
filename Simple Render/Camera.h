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
	private:
		GLFWwindow* window;
		mat4 viewMatrix;
		mat4 projMatrix;

		vec3 position;
		vec2 rotation;
		double lastTime;
		float speed;
		vec2 screenCenter;
		float fov;
		float aspectRatio;

		float mouseSens;
};
