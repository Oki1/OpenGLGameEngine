#include "Headers/input.hpp"

void ipt::updateInput(GLFWwindow* wd, Camera& cam, float deltaTime) {
	if (glfwGetKey(wd, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(wd, true);
	}
	if (glfwGetKey(wd, GLFW_KEY_A) == GLFW_PRESS) {
		cam.processKeyboard(CAM_LEFT, deltaTime);
	}
	if (glfwGetKey(wd, GLFW_KEY_D) == GLFW_PRESS) {
		cam.processKeyboard(CAM_RIGHT, deltaTime);
	}
	if (glfwGetKey(wd, GLFW_KEY_W) == GLFW_PRESS) {
		cam.processKeyboard(CAM_FORWARD, deltaTime);
	}
	if (glfwGetKey(wd, GLFW_KEY_S) == GLFW_PRESS) {
		cam.processKeyboard(CAM_BACKWARD, deltaTime);
	}
	if (glfwGetKey(wd, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		cam.processKeyboard(CAM_UP, deltaTime);
	}
	if (glfwGetKey(wd, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		cam.processKeyboard(CAM_DOWN, deltaTime);
	}

	double xpos;
	double ypos;
	glfwGetCursorPos(wd, &xpos, &ypos);
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	else {
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		if (xoffset != 0 || yoffset != 0) {
			cam.processMouse(xoffset, yoffset);
		}
		lastX = xpos;
		lastY = ypos;
	}
}