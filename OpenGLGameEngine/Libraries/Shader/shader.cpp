#include "Headers/shader.hpp"

#include <glad/gl.h>

#include <fstream>
#include <string>
#include <iostream>

void Shader::setInt(std::string name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(std::string name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setMat4(std::string name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, glm::value_ptr(value));    
}
void Shader::setMat3(std::string name, glm::mat3 value) {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, false, glm::value_ptr(value));

}
void Shader::setVec3(std::string name, glm::vec3 vec) {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
}
void Shader::setVec3(std::string name, float a, float b, float c) {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(glm::vec3(a, b, c)));
}

Shader::Shader(std::string vertexName, std::string fragmentName) {

	std::string vertexPath = shaderPath + vertexName;
	std::string fragmentPath = shaderPath + fragmentName;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	//std::cout << vertexPath << "\n" << fragmentPath << "\n";
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	std::string fragmentShaderSource;
	std::string vertexShaderSource;

	if (vertexFile.is_open()) {
		vertexShaderSource.assign((std::istreambuf_iterator<char>(vertexFile)),
			(std::istreambuf_iterator<char>()));
		vertexFile.close();
	} 
	else {
		std::cerr << "Vertex file opening failed" << std::endl;
	}
	if (fragmentFile.is_open()) {
		fragmentShaderSource.assign((std::istreambuf_iterator<char>(fragmentFile)),
			(std::istreambuf_iterator<char>()));
		fragmentFile.close();
	}
	else {
		std::cerr << "Fragment file opening failed" << std::endl;
	}

	const char* f_shader_code = fragmentShaderSource.c_str();
	const char* v_shader_code = vertexShaderSource.c_str();

    unsigned int vertex, fragment;
    int success;
    char info_log[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);


    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::use() {
    glUseProgram(ID);
}
void Shader::del() {
    glDeleteProgram(ID);
}