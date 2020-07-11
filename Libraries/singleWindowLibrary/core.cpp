#include "singleWindowLibrary.hpp"

void swl::clear() {
    glClearColor((float)background_color.r / 256, (float)background_color.g / 256, (float)background_color.b / 256, (float)background_color.a / 256);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void swl::updateScreen() {
    glfwSwapBuffers(swl::window);
    glfwPollEvents();
}

