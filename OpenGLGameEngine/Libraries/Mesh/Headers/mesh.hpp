#pragma once
#include <vector>
#include <iostream>

#include <shader.hpp>
#include <vertexAttributeArray.hpp>
#include <texture.hpp>



class Mesh {
public:
	char* allocateVertexBuffer(int nVertices, int vertexByteSize);
	
	void debugPrint();

	//Mesh(s_vertices vertices, s_indices indices, std::vector<Texture> textures);
	Mesh(std::string path);
	~Mesh();
	void Draw(Shader& shader); //idk if im gonna need this we'll see



private:
	float* vertexBuffer; // BUFFER IS INTERLACED
	unsigned int* indicesBuffer;
	unsigned int* indices;
	int numVertices;
	int numFaces;

	AttrArray aa;

	void setupMesh();
};