#include "Window/Headers/window.hpp"
#include "Input/Headers/input.hpp"
#include "Shader/Headers/shader.hpp"
#include "VertexAttributeArray/Header/vertexAttributeArray.hpp"
#include "Texture/Headers/Texture.hpp"

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
};


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    //std::cout << "mousex: " << xpos << "    mousey:" << ypos << std::endl;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    //std::cout << "scroll: " << yoffset << std::endl;
}
void key_callback(GLFWwindow* window, int key, int scanode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(wnd::window, true);
    }
}

int main(void) {
    //glfw, glew, input initiation
    //-------------------------------------------------------------------\  
    wnd::initial_title = "<3 u :3";//                                     \ 
    wnd::init(); //initiates glew and a glfw window                        \ 
    GLFWwindow* window = wnd::window;//                                     \ 
    ipt::inputinit(mouse_callback, scroll_callback, key_callback, window);//|
    //---------------------------------------------------------------------/
    Shader shader("triangle.vert", "triangle.frag");

    // GENERATE VAO
    //----------------------------------------------------------------------------
    AttrArray VAA;
    VAA.loadVAO();
    VAA.loadVBO(vertices, sizeof(vertices));
    VAA.loadEBO(indices, sizeof(indices));// generates EBO=> element buffer object. Less pixels=> indicies. yes im too lazy to write real comments. fuck off
    VAA.addData(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    VAA.enableVAA(0);
    // color attribute
    VAA.addData(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAA.enableVAA(1);
    // texture coord attribute
    VAA.addData(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAA.enableVAA(2);

    // load and create a texture 
// -------------------------------------------------------------------------------
    Texture texture1("container.jpg");
    Texture texture2("awesomeface.png", true);
    shader.use();
    shader.setInt("texture1", 0); //connects variable name in fragment shader to right texture units
    shader.setInt("texture2", 1);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); <=wireframe mode
    while (!glfwWindowShouldClose(window)) {// main render loop
        //RENDERING
        //------------------------------------------
        wnd::clear();
        shader.use();
        VAA.bindVAO();
        texture1.bindTex(GL_TEXTURE0);
        texture2.bindTex(GL_TEXTURE1);
        VAA.bindVAO();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //checks event triggers, updates window state and calls callback functions
        wnd::updateScreen();
    }
    shader.del();
    glfwTerminate();// terminates the window after the render loop
    std::cout << "Main render loop over, window terminated" << std::endl;
    //glDeleteProgram(shaderProgram);
}
