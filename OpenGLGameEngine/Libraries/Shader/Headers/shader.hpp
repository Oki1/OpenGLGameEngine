#ifndef SHADER_H
#define SHADER_H
#include <string>

class Shader {
public:
    unsigned int ID;
    std::string shaderPath = "./Resources/Shaders/";
    Shader(std::string vertexName, std::string fragmentName);

    void use();
    void del();
    void setInt(std::string name, int value);
};
#endif