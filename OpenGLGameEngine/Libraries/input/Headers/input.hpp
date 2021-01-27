#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace ipt {
	void inputinit(GLFWcursorposfun mcall, GLFWscrollfun scall, GLFWkeyfun kcall, GLFWwindow* wd);
}