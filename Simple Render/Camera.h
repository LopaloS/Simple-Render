#include "glm.hpp"
#include <glfw3.h>
using namespace glm;

class Camera
{
	public:
		Camera(GLFWwindow*,float, vec2);
		void Update();
		mat4 GetViewProjMatrix();
	private:
		GLFWwindow* window;
		mat4 viewProjMatrix;

		vec3 position;
		vec2 rotation;
		double lastTime;
		float speed;
		vec2 screenCenter;
		float fov;
		float aspectRatio;

		float mouseSens;
};
