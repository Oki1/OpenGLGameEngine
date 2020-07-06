#include "opengl.hpp"
#include "singleWindowLibrary.hpp"

bool swl::init() {
    window = glfwCreateWindow(initial_window_width, initial_window_height, initial_window_title.c_str(), nullptr, nullptr); // nullptr is for c++, NULL is for c
    if(!window) { // window == 0
        std::cerr << "Failed to create GLFW window" << std::endl;
        //glfwTerminate(); // it gets terminated in initScript
        return false;
    }
    //glfwPollEvents();
    //glfwSetWindowSize(window, 1920, 1080);
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}
