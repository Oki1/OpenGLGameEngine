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
        void setMat3(const std::string &name, glm::mat3 value) const;
        void setVec3(const std::string &name, glm::vec3 value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setTransformations(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const;
        //void setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) const;
        //void setMaterial(float ambientx, float ambienty, float ambientz, float diffusex, float diffusey, float diffusez, float specularx, float speculary, float specularz, float shininess) const;
        void setLight(float ambientx, float ambienty, float ambientz, float diffusex, float diffusey, float diffusez, float specularx, float speculary, float specularz, glm::vec3 position) const;
    };
}
#endif