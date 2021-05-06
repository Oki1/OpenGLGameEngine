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
    void setFloat(std::string name, float value);
    void setInt(std::string name, int value);
    void setMat4(std::string name, glm::mat4 mat);
    void setMat3(std::string name, glm::mat3 mat);
    void setVec3(std::string name, glm::vec3 vec);
    void setVec3(std::string name, float a, float b, float c);
};