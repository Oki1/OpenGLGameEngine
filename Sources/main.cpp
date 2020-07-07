#include "init.hpp"
#include "singleWindowLibrary.hpp"
#include <cmath>
//#include <string>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main() {\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 vertexColor;"
                                   "void main() {\n"
                                   "   FragColor = vertexColor;\n"
                                   "}\0";

void framebuffer_size_callback(GLFWwindow* window, int height, int width) {
    glViewport(0, 0, width, height);
}

int main() {
    swl::initial_window_height = 600;
    swl::initial_window_width = 800;
    swl::initial_window_title = "Test";
    swl::background_color = {141, 121, 126, 255};
    swl::init();



    //COMPILE VERTEX SHADER
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char info_log[512];
    glGetProgramiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(vertexShader, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << info_log << std::endl;
    }

    //COMPILE FRAGMENT SHADER
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(fragmentShader, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << info_log << std::endl;
    }


    //CREATE SHADER OBJECT
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info_log);
        std::cout <<"ERROR::SHADER::PROGRAM ::LINKING_FAILED\n"<<info_log << std::endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);


    //SAVES THE VERTEX POSITIONS IN GPU MEMORY FOR FAST ACCESS

    float vertices[] =
            {0.6f,  0.6f, 0.0f,// top right
             0.5f, -0.5f, 0.0f,// bottom right
             -0.4f, -0.4f, 0.0f,// bottom left
             -0.5f,  0.5f, 0.0};

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


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)nullptr);
    glEnableVertexAttribArray(0);


    glEnableVertexAttribArray(0);//UNBIND
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: "<< nrAttributes<< std::endl;
    //RENDER LOOP
    while(!glfwWindowShouldClose(swl::window)) {
        //INPUT
        if (swl::buttonPressed(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(swl::window, true);
        
        //RENDERING
        swl::clear();

        glUseProgram(shaderProgram);
        //update uniform
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"vertexColor");

        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        //render the square
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //EVENTS AND BUFFERS
        swl::updateScreen(); //checks event triggers, updates window state and calls callback functions
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    return 0;
}