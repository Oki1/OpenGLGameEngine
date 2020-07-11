#ifndef SHADER_H
#define SHADER_H

#include <glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace shd{
    class Shader{
    public:
        unsigned int ID;
        Shader(const char*vertexPath,const char*fragmentPath);

        void use();
        void del();

        void setBool(const std::string &name,bool value)const;
        void setInt(const std::string &name,int value)const;
        void setFloat(const std::string &name,float value)const;
        void setMat4(const std::string &name, glm::mat4 value) const;
    };
}
#endif