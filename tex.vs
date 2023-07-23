#version 430 core //tells pixel colors
in vec3 vert_pos;
in vec2 tex_coord;

uniform sampler2D texture1;


out vec4 FragColor;
void main() {
    FragColor = texture(texture1, tex_coord);
}