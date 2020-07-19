#include "shader.hpp"

//#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "glad.h"
#include <iostream>
#include <fstream>
#include <streambuf>


using namespace shd;

Shader::Shader(const char* vertex_path, const char* fragment_path) {
    std::ifstream vertex_file(vertex_path);
    std::string vertex_code;

    if(!vertex_file.is_open())
        std::cerr <<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n"<< std::endl;
    
    vertex_file.seekg(0, std::ios::end);
    vertex_code.reserve(vertex_file.tellg());
    vertex_file.seekg(0, std::ios::beg);
    
    vertex_code.assign((std::istreambuf_iterator<char>(vertex_file)), std::istreambuf_iterator<char>());
    vertex_file.close();
    
    std::ifstream fragment_file(fragment_path);
    std::string fragment_code;
    
    if(!fragment_file.is_open())
        std::cerr <<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n"<< std::endl;
    
    fragment_file.seekg(0, std::ios::end);
    fragment_code.reserve(fragment_file.tellg());
    fragment_file.seekg(0, std::ios::beg);
    
    fragment_code.assign((std::istreambuf_iterator<char>(fragment_file)), std::istreambuf_iterator<char>());
    fragment_file.close();
    
    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();
    
    unsigned int vertex, fragment;
    int success;
    char* info_log = nullptr;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        info_log = new char[512];
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        if(!info_log)
            info_log = new char[512];
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<info_log << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);


    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        if(!info_log)
            info_log = new char[512];
        glGetProgramInfoLog(ID, 512, nullptr, info_log);
        std::cout <<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<  info_log << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}



void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::del() {
    glDeleteProgram(ID);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x,y,z);
}

void Shader::setTransformations(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const {
    Shader::setMat4("model", model);
    Shader::setMat4("view", view);
    Shader::setMat4("projection", projection);
}

void Shader::setMat3(const std::string &name, glm::mat3 value) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
