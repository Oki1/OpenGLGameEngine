#version 330 core
// ALL OF THE LIGHTING CALCULATIONS ARE MADE IN VIEW SPACE
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 transposeModel;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;
void main() {
    normal = transposeModel * aNormal;
    fragPos = vec3(view * model * vec4(aPos, 1.0));
    texCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}