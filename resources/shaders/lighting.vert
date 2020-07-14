#version 330 core
// ALL OF THE LIGHTING CALCULATIONS ARE MADE IN VIEW SPACE
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transposeModel;

out vec3 fragPos;
out vec3 normal;
void main() {
    normal = mat3(transposeModel) * aNormal;
    fragPos = vec3(view * model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}