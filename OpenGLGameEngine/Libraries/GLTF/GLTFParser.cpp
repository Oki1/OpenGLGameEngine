#include "Headers/GLTFParser.hpp"

GLTF(std::string filename, std::string path = "Resources/Models/") : path{ path }, filename{ filename } {
	file = std::ifstream.open(path + filename, std::ifstream::in | std::ifstream::binary);
	file.seekg(4, file.cur); //skip magic
	file.read(&version, 4); //read version
	file.read(&filesize, 4); //read filesize

	file.read(&jsonLength, 4); //read json length
	file.seekg(4, file.cur); //skip json chunk type bytes

	//NOW READ THE JSON. TODO
}
