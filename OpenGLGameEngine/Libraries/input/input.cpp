#include "Headers/input.hpp"
void ipt::inputinit(GLFWcursorposfun mcall, GLFWscrollfun scall, GLFWkeyfun kcall, GLFWwindow* wd) {
    glfwSetInputMode(wd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);// set input mode(i know :O)
    glfwSetCursorPosCallback(wd, mcall);
    glfwSetKeyCallback(wd, kcall);
    glfwSetScrollCallback(wd, scall);
}