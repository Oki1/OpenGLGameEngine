#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include "json/json.hpp"
#include <utility>
#include <Mesh/Headers/Mesh.hpp>
using json = nlohmann::json;
//glb file:
//first 12 bytes header, then another 4 bytes for the size of the json chunk, another 4 bytes of magic, then the data itself
class GLTF {
public:
	GLTF(std::string filename, std::string path = "Resources/Models/");
	~GLTF();

	std::string path;
	std::string filename;
	uint32_t version;
	json jsonObject;

	std::vector<Mesh> getMeshes();
	
private:
	struct chunk {
		uint32_t offset;
		uint32_t size;

	};
	struct arr {
		float* arr;
		unsigned int size;
	};
	std::ifstream file;
	uint32_t jsonLength;
	uint32_t filesize;

	std::vector<chunk> chunks;

	arr readPointData(std::string attribute, json mesh);

};