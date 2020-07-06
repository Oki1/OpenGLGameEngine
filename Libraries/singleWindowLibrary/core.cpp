#include "singleWindowLibrary.hpp"

void swl::clear() {
    glClearColor((float)background_color.r / 256, (float)background_color.g / 256, (float)background_color.b / 256, (float)background_color.a / 256);
    glClear(GL_COLOR_BUFFER_BIT);
}

void swl::updateScreen() {
    glfwSwapBuffers(swl::window);
    glfwPollEvents();
}

void swl::checkShader(int target_shader, std::string shader_type, std::string error_type) {
    int success;
    char info_log[512];
    glGetProgramiv(target_shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(target_shader, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::" << shader_type << "::COMPILATION_FAILED\n" << info_log << std::endl;
    }
}
