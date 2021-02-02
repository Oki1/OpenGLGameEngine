#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    unsigned int ID;
    std::string shaderPath = "./Resources/Shaders/";
    Shader(std::string vertexName, std::string fragmentName);

    void use();
    void del();
    void setInt(std::string name, int value);
    void setMat4(std::string name, glm::mat4 mat);
};