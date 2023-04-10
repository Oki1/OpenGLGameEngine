#pragma once
#include <glm/glm.hpp>


#include <shader.hpp>
#include <vertexAttributeArray.hpp>
#include <texture.hpp>

#include <string>
#include <vector>

struct s_Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TexCoords;
};


class Mesh {
public:
	std::vector<s_Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	Mesh(std::vector<s_Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader &shader); //idk if im gonna need this we'll see
private:
	AttrArray aa;

	void setupMesh();
};