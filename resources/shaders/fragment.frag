#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2) * vec4(vertexColor, 1.0);
//    FragColor = texture(texture1, texCoord);
}