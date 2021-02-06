#version 410 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
out vec4 FragColor;


uniform Material material;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 normal;
in vec3 fragPos;
void main() {
	//ambient light
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength*lightColor;


	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;


	vec3 result = (ambient + diffuse + specular) * objectColor;// (diffuse + ambient) * objectColor;

	FragColor = vec4(result, 1.0);
}