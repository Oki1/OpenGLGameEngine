#include "init.hpp"
#include "singleWindowLibrary.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "texture.hpp"

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int height, int width);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int generateTexture(std::string path);

Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));
float last_x = swl::initial_window_width / 2.0f;
float last_y = swl::initial_window_height / 2.0f;
bool first_mouse = true;

float last_time = 0.0f;
float delta_time;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {
    //initialization
    swl::initial_window_height = 600;
    swl::initial_window_width = 800;
    swl::initial_window_title = "Test";
    swl::background_color = { 0, 0, 0, 255 };
    swl::init();
    glfwSetFramebufferSizeCallback(swl::window, framebuffer_size_callback);
    glfwSetCursorPosCallback(swl::window, mouse_callback);

    //buffer data
    glm::vec3 cube_positions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };
    glm::vec3 point_light_positions[] = {
            glm::vec3(0.7f, 0.2f, 2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f, 2.0f, -12.0f),
            glm::vec3(0.0f, 0.0f, -3.0f)
    };
    float vertices[] = {
        // positions // normals // texture coords
                    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
                    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
                    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
                    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int VBO, containerVAO; //VAO CONTAINER
    glGenVertexArrays(1, &containerVAO);
    glBindVertexArray(containerVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //texture coordinate
    glEnableVertexAttribArray(2);
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //textures
    tex::Texture containerTex("container2.png");
    tex::Texture containerSpecTex("container2_specular.png");

    //generate shader program
    shd::Shader lighting("lighting", "lighting");
    shd::Shader light_object("lightObject", "lightObject");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, containerTex.id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, containerSpecTex.id);

    lighting.use();
    lighting.setInt("material.diffuse", 0);
    lighting.setInt("material.specular", 1);
    lighting.setFloat("material.shininess", 32.0f);

    float quadratic = 0.017f;
    float linear = 0.07f;
    float constant = 1.0f;
    float specular = 0.0f; //1.0f;
    float diffuse = 0.8f; //0.8f;
    float ambient = 0.0f; //0.2f;
    lighting.setVec3("pointLight[0].ambient", glm::vec3(ambient));
    lighting.setVec3("pointLight[0].diffuse", glm::vec3(diffuse));
    lighting.setVec3("pointLight[0].specular", glm::vec3(specular));
    lighting.setFloat("pointLight[0].constant", constant);
    lighting.setFloat("pointLight[0].linear", linear);
    lighting.setFloat("pointLight[0].quadratic", quadratic);
    lighting.setVec3("pointLight[0].position", point_light_positions[0]);

    lighting.setVec3("pointLight[1].ambient", glm::vec3(ambient));
    lighting.setVec3("pointLight[1].diffuse", glm::vec3(diffuse));
    lighting.setVec3("pointLight[1].specular", glm::vec3(specular));
    lighting.setFloat("pointLight[1].constant", constant);
    lighting.setFloat("pointLight[1].linear", linear);
    lighting.setFloat("pointLight[1].quadratic", quadratic);
    lighting.setVec3("pointLight[1].position", point_light_positions[1]);

    lighting.setVec3("pointLight[2].ambient", glm::vec3(ambient));
    lighting.setVec3("pointLight[2].diffuse", glm::vec3(diffuse));
    lighting.setVec3("pointLight[2].specular", glm::vec3(specular));
    lighting.setFloat("pointLight[2].constant", constant);
    lighting.setFloat("pointLight[2].linear", linear);
    lighting.setFloat("pointLight[2].quadratic", quadratic);
    lighting.setVec3("pointLight[2].position", point_light_positions[2]);

    lighting.setVec3("pointLight[3].ambient", glm::vec3(ambient));
    lighting.setVec3("pointLight[3].diffuse", glm::vec3(diffuse));
    lighting.setVec3("pointLight[3].specular", glm::vec3(specular));
    lighting.setFloat("pointLight[3].constant", constant);
    lighting.setFloat("pointLight[3].linear", linear);
    lighting.setFloat("pointLight[3].quadratic", quadratic);
    lighting.setVec3("pointLight[3].position", point_light_positions[3]);

    lighting.setVec3("dirLight.ambient", glm::vec3(ambient));
    lighting.setVec3("dirLight.diffuse", glm::vec3(diffuse));
    lighting.setVec3("dirLight.specular", glm::vec3(specular));
    lighting.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

    lighting.setVec3("spotLight.direction", camera.front);
    lighting.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    lighting.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    lighting.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    lighting.setFloat("spotLight.constant", 1.0f);
    lighting.setFloat("spotLight.linear", 0.09);
    lighting.setFloat("spotLight.quadratic", 0.032);
    lighting.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    lighting.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
    lighting.setVec3("spotLight.position", glm::vec4(camera.position, 1.0f));


    while (!glfwWindowShouldClose(swl::window)) {
        //calc delta time
        float currentFrame = glfwGetTime();
        delta_time = currentFrame - last_time;
        last_time = currentFrame;
        //INPUT1
        processInput(swl::window);
        //RENDERING
        swl::clear();
        //creates matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)swl::initial_window_width / (float)swl::initial_window_height, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        //light object
        glm::mat4 model(1.0f);
        light_object.use();
        light_object.setMat4("view", view);
        light_object.setMat4("projection", projection);
        for (int i = 0; i < 4; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, point_light_positions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            light_object.setMat4("model", model);
            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //cube
        model = glm::mat4(1.0f);
        lighting.use();
        lighting.setVec3("viewPos", camera.position);
        lighting.setMat4("view", view);
        lighting.setMat4("projection", projection);
        lighting.setMat3("transposeModel", glm::mat3(glm::transpose(glm::inverse(model))));
        for (unsigned int i = 0; i < 10; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cube_positions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lighting.setMat4("model", model);
            glBindVertexArray(containerVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //EVENTS AND BUFFERS
        swl::updateScreen(); //checks event triggers, updates window state and calls callback functions
    }
    glDeleteVertexArrays(1, &containerVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    lighting.del();
    light_object.del();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(swl::window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(FORWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(BACKWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(LEFT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(RIGHT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.processKeyboard(UP, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera.processKeyboard(DOWN, delta_time);
    }

}
void framebuffer_size_callback(GLFWwindow* window, int height, int width) {
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (first_mouse) {
        last_x = xpos;
        last_y = ypos;
        first_mouse = false;
    }

    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos; // reversed since y-coordinates go from bottom to top

    last_x = xpos;
    last_y = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}
