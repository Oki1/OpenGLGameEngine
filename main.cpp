#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int height, int width) {
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Test", NULL, NULL);
    if (window == NULL) {
        std::cerr <<"Failed to create GLFW window"<< std::endl;
        glfwTerminate();
        return-1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr <<"Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0,0,1920,1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //RENDER LOOP
    while(!glfwWindowShouldClose(window)) {
        //INPUT
        processInput(window);

        //RENDERING
        glClearColor(0.431f, 0.796f, 0.266f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //EVENTS AND BUFFERS
        glfwSwapBuffers(window);
        glfwPollEvents(); //checks event triggers, updates window state and calls callback functions
    }

    glfwTerminate();
    return 0;
}