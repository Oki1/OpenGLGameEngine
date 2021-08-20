#pragma once
#include <vector>
#include "Texture/Headers/Texture.hpp"
#include "Shader/Headers/shader.hpp"
#include "VertexAttributeArray/Header/vertexAttributeArray.hpp"
struct s_vertices {
	float* pos;
	float* nor;
	float* tex;
	unsigned int nVerts;
};
struct s_indices {
	uint16_t* indices;
	unsigned int nIndices;
};


class Mesh {
public:
	s_vertices vertices;
	s_indices indices;
	std::vector<Texture> textures;

	Mesh(s_vertices vertices, s_indices indices, std::vector<Texture> textures);
	~Mesh();
	void Draw(Shader& shader); //idk if im gonna need this we'll see
private:
	AttrArray aa;

	void setupMesh();
};