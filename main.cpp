#include <GLFW/glfw3.h>
#include <iostream>


void error_callback(int error, const char* description) {
    std::cerr << "Error: %s\n" << description;
}


int main() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
    }


    GLFWwindow* window = glfwCreateWindow(1920, 1080, "TestWindow", NULL, NULL);
    if(!window) {
        std::cerr << "window creation failed" << std::endl;
    }

    short i;
    std::cin >> i;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}