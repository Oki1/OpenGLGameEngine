#pragma once
#include <vector>
#include <iostream>

#include <shader.hpp>
#include <vertexAttributeArray.hpp>
#include <Texture.hpp>

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
	char* allocateVertexBuffer(int nVertices, int vertexByteSize);
	
	void debugPrint();




	/*s_vertices vertices;
	s_indices indices;
	std::vector<Texture> textures;*/
	char* vertices;
	char* indices;

	//Mesh(s_vertices vertices, s_indices indices, std::vector<Texture> textures);
	~Mesh();
	void Draw(Shader& shader); //idk if im gonna need this we'll see



private:
	char* vertexBuffer; // BUFFER IS INTERLACED
	int numVertices;









	AttrArray aa;

	void setupMesh();
};