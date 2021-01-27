#include "Headers/shader.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <glad/glad.h>

void Shader::setInt(std::string name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
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