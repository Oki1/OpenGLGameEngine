#version 330 core
// ALL OF THE LIGHTING CALCULATIONS ARE MADE IN VIEW SPACE
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};
out vec4 fragColor;

in vec2 texCoords;
in vec3 fragPos;
in vec3 normal;
uniform Material material;
uniform Light light;
void main() {
    vec3 ambient = texture(material.diffuse, texCoords).rgb * light.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular, texCoords).rgb * spec * light.specular;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}