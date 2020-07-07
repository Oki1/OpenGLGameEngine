#include "init.hpp"
#include "singleWindowLibrary.hpp"
#include "shader.h"
#include <cmath>
//#include <string>


void framebuffer_size_callback(GLFWwindow* window, int height, int width) {
    glViewport(0, 0, width, height);
}

int main() {
    swl::initial_window_height = 600;
    swl::initial_window_width = 800;
    swl::initial_window_title = "Test";
    swl::background_color = {141, 121, 126, 255};
    swl::init();



    shd::Shader shaderProgram("../resources/shaders/vertex.vert", "../resources/shaders/fragment.frag");

    float vertices[] =
            {0.6f,  0.6f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
             -0.4f, -0.4f, 0.0f, 0.0f, 1.0f, 0.0f,
             -0.5f,  0.5f, 0.0, 1.0f, 1.0f, 0.0f};
    unsigned int indicies[] = {
            0,1,3, //FIRST TRIANGLE
            1,2,3  //SECOND TRIANGLE
    };


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);  //STORE THE VERTICIES IN A BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //STORES THE INDICIES IN A BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


//    uncomment this call to draw in wireframe polygons.
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    int nrAttributes;
//    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//    std::cout << "Maximum nr of vertex attributes supported: "<< nrAttributes<< std::endl;

    //RENDER LOOP
    while(!glfwWindowShouldClose(swl::window)) {
        //INPUT
        if (swl::buttonPressed(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(swl::window, true);
        
        //RENDERING
        swl::clear();

        shaderProgram.use();
        //render the square
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //EVENTS AND BUFFERS
        swl::updateScreen(); //checks event triggers, updates window state and calls callback functions
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shaderProgram.del();
    return 0;
}