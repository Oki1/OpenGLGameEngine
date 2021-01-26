#version 330 core
// ALL OF THE LIGHTING CALCULATIONS ARE MADE IN WORLD SPACE
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
#define POINT_LIGHT_NUM 4
struct sPointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
};
uniform sPointLight pointLight[POINT_LIGHT_NUM];
vec3 calcPointLight(sPointLight light, vec3 difTex, vec3 specTex, vec3 norm, vec3 fragPosition, vec3 viewDir);

struct sDirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform sDirLight dirLight;
vec3 calcDirLight(sDirLight light, vec3 difTex, vec3 specTex, vec3 norm, vec3 viewDir);

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLight;
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 difTex, vec3 specTex);

out vec4 fragColor;

in vec2 texCoords;
in vec3 fragPos;
in vec3 normal;
uniform Material material;
uniform vec3 viewPos;
void main() {
    vec3 difTex = texture(material.diffuse, texCoords).rgb;
    vec3 specTex = texture(material.specular, texCoords).rgb;
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 result = vec3(0.0);
    for(int i = 0; i < POINT_LIGHT_NUM; i++) {
        result += calcPointLight(pointLight[i], difTex, specTex, norm, fragPos, viewDir);
    }
    result += calcDirLight(dirLight, difTex, specTex, norm, viewDir);
    result += calcSpotLight(spotLight, norm, fragPos, viewDir, difTex, specTex);
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
vec3 calcDirLight(sDirLight light, vec3 difTex, vec3 specTex, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * difTex;
    vec3 diffuse = light.diffuse * diff * difTex;
    vec3 specular = light.specular * spec * specTex;
    return (ambient + diffuse + specular);
}
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 difTex, vec3 specTex)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * difTex;
    vec3 diffuse = light.diffuse * diff * difTex;
    vec3 specular = light.specular * spec * specTex;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}