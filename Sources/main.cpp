#include "init.hpp"
#include "singleWindowLibrary.hpp"
#include "shader.h"
#include <cmath>
#include "stbImage.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


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

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); //create texture object and bind it

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels; //load and generate the texture
    unsigned char *data = stbi_load("../resources/textures/container.jpg", &width, &height, &nrChannels, 0);

    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("../resources/textures/awesomeface.png", &width, &height,&nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


//    uncomment this call to draw in wireframe polygons.
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    int nrAttributes;x
//    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//    std::cout << "Maximum nr of vertex attributes supported: "<< nrAttributes<< std::endl;




    //RENDER LOOP
    shaderProgram.use();
    shaderProgram.setInt("texture2", 1);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram.ID, "transform");
    while(!glfwWindowShouldClose(swl::window)) {
        //INPUT
        if (swl::buttonPressed(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(swl::window, true);
        
        //RENDERING
        swl::clear();
        shaderProgram.use();
        //creates transformation matrix
        //ROTATION HAS TO BE FIRST DUE TO HOW MATRICES ARE MULTIPLIED
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //adds transform uniform
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //adds textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
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