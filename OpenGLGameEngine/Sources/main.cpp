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
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

int main(void) {
    const float fov = 75.0f;

    //glfw, glew, input initiation
    //-------------------------------------------\ 
    wnd::initial_title = "<3 u :3";//             \ 
    wnd::background_color = { 0,0,0 };//           \ 
    wnd::init(); //initiates glew and a glfw window \ 
    GLFWwindow* window = wnd::window;//              \
    //------------------------------------------------\ 
    Shader shader("triangle.vert", "triangle.frag");
    Shader lightShader("lightObject.vert", "lightObject.frag");


    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 obPos(1.0f, 1.0f, 1.0f);

    // GENERATE VAO
    //----------------------------------------------------------------------------
    AttrArray VAA;
    VAA.loadVAO();
    VAA.loadVBO(vertices, sizeof(vertices));
    VAA.addData(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    VAA.enableVAA(0);// configure attribute
    VAA.addData(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    VAA.enableVAA(1);


    //light vao
    AttrArray lightOb;
    lightOb.loadVAO();
    glBindBuffer(GL_ARRAY_BUFFER, VAA.VBO);
    lightOb.addData(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    VAA.enableVAA(0);

    // load and create a texture 
// -------------------------------------------------------------------------------
    
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
        if (aspectRatio != lastAr) {
            projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
        }

        //send other shit to gpu


        //send matrices to gpu
        shader.use();
        shader.setVec3("objectColor", 1.0f, 0.0f, 0.0f);
        shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        shader.setVec3("lightPos", lightPos);
        shader.setVec3("viewPos", camera.camPos);

        shader.setMat3("transposeMatrix", glm::mat3(glm::transpose(glm::inverse(model))));

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        VAA.bindVAO();
        glDrawArrays(GL_TRIANGLES, 0, 36);



        lightShader.use();
        glm::mat4 lMod = glm::mat4(1.0f);
        lMod = glm::translate(lMod, lightPos);
        lMod = glm::scale(lMod, glm::vec3(0.2f));
        lightShader.setMat4("model", lMod);
        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);
        lightOb.bindVAO();
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