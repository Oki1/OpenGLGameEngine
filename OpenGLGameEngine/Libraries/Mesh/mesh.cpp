#include "Headers/mesh.hpp"


Mesh::Mesh(std::vector<s_Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :vertices(vertices), indices(indices), textures(textures) {
	setupMesh();
}

void Mesh::setupMesh() {
	//generate VAO
	aa.loadVAO();
	aa.loadVBO(&vertices[0], vertices.size() * sizeof(s_Vertex));
	aa.loadEBO(&indices[0], indices.size() * sizeof(unsigned int));
	aa.enableVAA(0);
	aa.addData(0, 3, GL_FLOAT, GL_FALSE, sizeof(s_Vertex), (void*)0);
	aa.enableVAA(1);
	aa.addData(1, 3, GL_FLOAT, GL_FALSE, sizeof(s_Vertex), (void*)offsetof(s_Vertex, Normal));
	aa.enableVAA(2);
	aa.addData(2, 2, GL_FLOAT, GL_FALSE, sizeof(s_Vertex), (void*)offsetof(s_Vertex, TexCoords));
	aa.bindVAO();
}
void Mesh::Draw(Shader& shader) {
	//textures
	unsigned int diffuse = 1;
	unsigned int specular = 1;
	for (unsigned int i = 0, n = textures.size(); i < n; i++) {
		std::string name;
		std::string number;
		if (textures[i].type == DIFFUSE) {
			name = "texture_diffuse";
			number = std::to_string(diffuse++);
		}
		else {
			name = "texture_specular";
			number = std::to_string(specular++);

		}
		shader.setFloat(("material." + name + number).c_str(), i);
		textures[i].bindTex(GL_TEXTURE0 + i);
	}

	//rendering
	aa.bindVAO();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	aa.unbindVAO();
}