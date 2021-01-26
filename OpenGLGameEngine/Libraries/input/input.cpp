#include "Headers/input.hpp";
#include "window/Headers/window.hpp"

void ipt::inputInit(
static void mouse_callback(GLFWwindow* window, double xpos, double ypos),
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset),
static void key_callback(GLFWwindow* window, int key, int scanode, int action, int mods)) {
	glfwSetCursorPosCallback(wnd::window, mouse_callback);
	glfwSetKeyCallback(wnd::window, key_callback);
	glfwSetScrollCallback(wnd::window, scroll_callback);
}