#include "singleWindowLibrary.hpp"
#include "opengl.hpp"

void swl::clear() {
    glClearColor((float)background_color.r / 256, (float)background_color.g / 256, (float)background_color.b / 256, (float)background_color.a / 256);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void swl::updateScreen() {
    glfwSwapBuffers(swl::window);
    glfwPollEvents();
}

bool swl::init() {
    window = glfwCreateWindow(initial_window_width, initial_window_height, initial_window_title.c_str(), nullptr, nullptr); // nullptr is for c++, NULL is for c
    if (!window) { // window == 0
        std::cerr << "Failed to create GLFW window" << std::endl;
        //glfwTerminate(); // it gets terminated in initScript
        return false;
    }
    //glfwPollEvents();
    //glfwSetWindowSize(window, 1920, 1080);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST); //enable depth testing
    return true;
}
