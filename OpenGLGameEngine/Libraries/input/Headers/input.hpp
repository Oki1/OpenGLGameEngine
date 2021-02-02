#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera/Headers/camera.hpp"

namespace ipt {
	static bool firstMouse = true;
	static double lastX;
	static double lastY;

	void updateInput(GLFWwindow* wd, Camera& cam, float deltaTime);
}