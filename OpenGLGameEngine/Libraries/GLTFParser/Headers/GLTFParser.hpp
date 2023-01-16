#pragma once
typedef unsigned int uint;
#include <Mesh.hpp>

#include <rapidjson/document.h>

#include <string>
#include <vector>

class GLTFParser {
public:
	GLTFParser(std::string path, std::string filename);
	~GLTFParser();
	std::vector<Mesh> getMeshes();
private:
	std::string path, filename;

	struct saccessor {
		uint BVOffset; //buffer view byte offset
		uint type; // 0 for SCALAR 1 for VEC
		uint typen; // dim of vector. undefined for SCALAR
		uint componentType;
		uint count;
		uint byteOffset;
		uint byteLength;
		uint byteStride;
		uint buffer;
		uint componentByteSize;
	};
	std::vector<saccessor> accessors;
	char* jsonBuffer;
	char** dataBuffers;
	char* returnDataBuffer(uint index);
	int nBuffers;
	rapidjson::Document doc;

};
/*#include <cstdint>
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

};*/