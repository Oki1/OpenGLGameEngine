#pragma once
#include <GLFW/glfw3.h>

namespace ipt {
	void inputInit(
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos),
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset),
		static void key_callback(GLFWwindow* window, int key, int scanode, int action, int mods));
}