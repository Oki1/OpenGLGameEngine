#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm.hpp>

namespace shd {
    class Shader {
    public:
        unsigned int ID;
        Shader(const char* vertexPath, const char* fragmentPath);

        void use();
        void del();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, glm::mat4 value) const;
        void setMat3(const std::string &name, glm::mat3 value) const;
        void setVec3(const std::string &name, glm::vec3 value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setTransformations(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const;
    };
}
#endif
