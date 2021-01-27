#include "Headers/window.hpp"

void wnd::clear() {
    glClearColor((float)background_color.r / 255, (float)background_color.g / 255, (float)background_color.b / 255, (float)background_color.a / 255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void wnd::updateScreen() {
    glfwSwapBuffers(wnd::window);
    glfwPollEvents();
}





bool wnd::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);// version 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// choose core or immediet mode of opengl
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);// whether the window will be resizable
    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);

    window = glfwCreateWindow(initial_width, initial_height, initial_title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "GLFW window creation failed" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST);// enable depth testing (dont render pixels which are covered by others

    glViewport(0, 0, initial_width, initial_height);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            std::cerr << "window has been resized to " << width << "x" << height << std::endl;
            glViewport(0, 0, width, height);
        });

    return true;
}