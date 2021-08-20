#include "Headers/GLTFParser.hpp"
#include <iostream>
#include <bit>
using json = nlohmann::json;

GLTF::GLTF(std::string filename, std::string path) : path{ path }, filename{ filename } {
	file = std::ifstream(path + filename,	std::ifstream::binary);
	//HEADER
	file.seekg(4, file.cur); //skip magic
	file.read((char*)&version, sizeof(version)); //read version. sizeof version is 4 bytes
	file.read((char*)&filesize, sizeof(filesize)); //read filesize

	//JSON CHUNK
	file.read((char*)&jsonLength, sizeof(jsonLength)); //read json length
	file.seekg(4, file.cur); //skip json chunk type bytes
	//NOW READ THE JSON
	unsigned char* jsonBuffer = new unsigned char[jsonLength];
	file.read((char*)jsonBuffer, jsonLength);
	jsonObject = json::parse(jsonBuffer);
	delete jsonBuffer;

	//CHUNKS
	//loop over chunks and save the offsets and sizes
	int numberOfChunks = jsonObject["buffers"].size();
	for (int x = 0; x < numberOfChunks; x++) {
		chunk c;
		file.read((char*)&c.size, 4);
		file.seekg(4, file.cur); //skip chunkType
		c.offset = (uint32_t)file.tellg();
		chunks.push_back(c);
		file.seekg(c.size, file.cur); //skip to next chunk
	}
}

GLTF::arr GLTF::readPointData(std::string attribute, json mesh) {
	json accessor = jsonObject["accessors"][(int)mesh["primitives"][0]["attributes"][attribute]];
	json bufferView = jsonObject["bufferViews"][(int)accessor["bufferView"]];
	arr ar;
	ar.arr = (float*)new char[bufferView["byteLength"]];
	ar.size = accessor["count"];
	file.seekg(chunks[bufferView["buffer"]].offset + bufferView["byteOffset"], file.beg);
	file.read((char*)ar.arr, bufferView["byteLength"]);

	return ar;
}

std::vector<Mesh> GLTF::getMeshes() {
	for (auto x : jsonObject["meshes"]) {
		//position vector
		s_vertices verts;
		arr pos = readPointData("POSITION", x);
		verts.nVerts = pos.size;
		verts.pos = pos.arr;
		delete& pos;
		verts.nor = readPointData("NORMAL", x).arr;
		verts.tex = readPointData("TEXCOORD_0", x).arr;

		//indices
		s_indices ind;
		json accessor = jsonObject["accessors"][(int)x["primitives"][0]["indices"]];
		json bufferView = jsonObject["bufferViews"][(int)accessor["bufferView"]];
		ind.nIndices = accessor["count"];
		ind.indices = new uint16_t[ind.nIndices];
		file.seekg(chunks[bufferView["buffer"]].offset + bufferView["byteOffset"], file.beg);
		file.read((char*)ind.indices, bufferView["byteLength"]);

	}
	return std::vector<Mesh>();
}
GLTF::~GLTF() {
	file.clear();
	file.close();
}