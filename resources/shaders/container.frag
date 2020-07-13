#version 330 core
out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 normal;
in vec3 fragPos;
void main()
{

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm,lightDir), 0.0);
    vec3 diffuse = diff*lightColor;
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor * objectColor;
    vec3 result = (ambient + diffuse) * objectColor;
    fragColor = vec4(result, 1.0);
}