#include "Window/Headers/window.hpp"
#include "Input/Headers/input.hpp"
#include "Shader/Headers/shader.hpp"
#include "VertexAttributeArray/Header/vertexAttributeArray.hpp"
#include "Texture/Headers/Texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera/Headers/Camera.hpp"

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


int main(void) {
    const float fov = 75.0f;

    //glfw, glew, input initiation
    //-------------------------------------------\ 
    wnd::initial_title = "<3 u :3";//             \ 
    wnd::background_color = { 219, 144, 125 };//   \ 
    wnd::init(); //initiates glew and a glfw window \ 
    GLFWwindow* window = wnd::window;//              \
    //------------------------------------------------\ 
    Shader shader("triangle.vert", "triangle.frag");

    //Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

    // GENERATE VAO
    //----------------------------------------------------------------------------
    AttrArray VAA;
    VAA.loadVAO();
    VAA.loadVBO(vertices, sizeof(vertices));
    VAA.addData(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)0);
    VAA.enableVAA(0);
    // texture coord attribute
    VAA.addData(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    VAA.enableVAA(1);

    // load and create a texture 
// -------------------------------------------------------------------------------
    Texture texture1("container.jpg");
    Texture texture2("awesomeface.png", true);
    shader.use();
    shader.setInt("texture1", 0); //connects variable name in fragment shader to right texture units
    shader.setInt("texture2", 1);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //<=wireframe modes

    // different matrices i need
// -----------------------------------------------------\
    local space-model matrix
    glm::mat4 model(1.0f);
//  world space
//  view  space-camera
//  CAMERA
//-------------------------------------------
    glm::mat4 view = glm::mat4(1.0f);
    Camera camera = Camera();

//  projection matrix-(3dness)
    glm::mat4 projection = glm::mat4(1.0f);

    float aspectRatio = -1.0f;
    
    projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);

    double newTime = 0;
    double lastTime = 0;
    double deltaTime = 0;
    while (!glfwWindowShouldClose(window)) {// main render loop
        //update input
        //---------------------
        ipt::updateInput(window, camera, deltaTime);
        // Calculates DeltaTime(difference in time in seconds between this and last frame)
        // ----------------------------------------
        newTime = glfwGetTime();
        deltaTime = newTime - lastTime;
        lastTime = newTime;
        //RENDERING
        //------------------------------------------
        wnd::clear();
        //regen view matrix
        view = camera.getViewMatrix();
        //regen projection matrix if needed
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float lastAr = aspectRatio;
        aspectRatio = width / (float)height;

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.use();
        VAA.bindVAO();
        texture1.bindTex(GL_TEXTURE0);
        texture2.bindTex(GL_TEXTURE1);
        VAA.bindVAO();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //checks event triggers, updates window state and calls callback functions
        wnd::updateScreen();
    }
    shader.del();
    glfwTerminate();// terminates the window after the render loop
    std::cout << "Main render loop over, window terminated" << std::endl;
    //glDeleteProgram(shaderProgram);
    return 0;
}
