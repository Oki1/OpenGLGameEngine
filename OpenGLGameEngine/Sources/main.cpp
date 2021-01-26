#include "window/Headers/window.hpp"
#include "input/Headers/input.hpp"

static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "mousex: " << xpos << "    mousey:" << ypos << std::endl;
}
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "scroll: " << yoffset << std::endl;
}
static void key_callback(GLFWwindow* window, int key, int scanode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        std::cout << "Window quit" << std::endl;
        glfwSetWindowShouldClose(wnd::window, true);
    }
}

int main(void) {
    wnd::init(); //initiates glew and a glfw window
    wnd::initial_title = "Added name, okay?!";
    //sets up input callback functions
    ipt::inputInit(mouse_callback, scroll_callback, key_callback);

    while (!glfwWindowShouldClose(wnd::window)) {// main render loop
        //RENDERING
        //------------------------------------------
        wnd::clear();
        //checks event triggers, updates window state and calls callback functions
        wnd::updateScreen();
    }

    glfwTerminate();// terminates the window after the render loop
    std::cout << "Main render loop over, window terminated" << std::endl;
}
