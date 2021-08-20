#pragma once
#include <vector>
#include "Texture/Headers/Texture.hpp"
#include "Shader/Headers/shader.hpp"
#include "VertexAttributeArray/Header/vertexAttributeArray.hpp"
struct s_Vertex {
	float* pos;
	float* nor;
	float* tex;
};


class Mesh {
public:
	//std::vector<s_Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<s_Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();
	void Draw(Shader& shader); //idk if im gonna need this we'll see
private:
	AttrArray aa;

	void setupMesh();
};