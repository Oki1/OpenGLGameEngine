#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <camera.hpp>

#include <iostream>

namespace ipt {
	static bool firstMouse = true;
	static double lastX;
	static double lastY;

	void updateInput(GLFWwindow* wd, Camera& cam, float deltaTime);
}