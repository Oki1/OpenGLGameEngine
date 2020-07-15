#version 330 core
// ALL OF THE LIGHTING CALCULATIONS ARE MADE IN VIEW SPACE
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct sPointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
};
uniform sPointLight pointLight;
vec3 calcPointLight(sPointLight light, vec3 difTex, vec3 specTex, vec3 norm, vec3 fragPosition, vec3 viewDir);


out vec4 fragColor;

in vec2 texCoords;
in vec3 fragPos;
in vec3 normal;
uniform Material material;
void main() {
    vec3 difTex = texture(material.diffuse, texCoords).rgb;
    vec3 specTex = texture(material.specular, texCoords).rgb;
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(-fragPos);
    vec3 result = calcPointLight(pointLight, difTex, specTex, norm, fragPos, viewDir);
    fragColor = vec4(result, 1.0);
}

vec3 calcPointLight(sPointLight light, vec3 difTex, vec3 specTex, vec3 norm, vec3 fragPosition, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    vec3 ambient = difTex * light.ambient;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * difTex;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specTex * spec * light.specular;

    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    return( ambient + attenuation * (diffuse + specular));
}