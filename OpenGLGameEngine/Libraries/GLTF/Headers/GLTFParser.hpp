#pragma once
#include <string>
#include <cstdint>
#include <ifstream>
//glb file:
//first 12 bytes header, then another 4 bytes for the size of the json chunk, another 4 bytes of magic, then the data itself
class GLTF{
public:


	std::string path;
	std::string filename;
	GLTF(std::string filename, std::string path = "Resources/Models/");
	//~GLTF();
	uint32_t version;
	uint32_t filesize;

	uint32_t jsonLength;

private:
	std::ifstream file;
}