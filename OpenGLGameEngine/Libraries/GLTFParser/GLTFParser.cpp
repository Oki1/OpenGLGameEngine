#include <fstream>
#include <iostream>
#include <cstring>

#include "Headers/GLTFParser.hpp"

void parseNode(rapidjson::Value &nodes, int index) {
	rapidjson::Value& node = nodes[index];
	if(node.HasMember("children")) {
		for(auto& x : node["children"].GetArray()) {
			parseNode(nodes, x.GetInt());
		}
	}
	if(node.HasMember("mesh")) {
		
	}
}


GLTFParser::GLTFParser(std::string path, std::string filename): path(path), filename(filename) {
	std::cout << "Parsing begin" << std::endl;
	//load json file and parse json
	std::string fullPath = path+"/"+filename;
	std::ifstream file(fullPath, std::ios::binary | std::ios::ate);
	uint size = file.tellg();
	file.seekg(0, std::ios::beg);
	jsonBuffer = new char[size+1];
	if (file.read(jsonBuffer, size)) {
		std::cout << "Reading " << filename << " successful!"<<std::endl;
	} else {
		std::cout << "Failed to read from file "<<filename <<std::endl;
	}
	jsonBuffer[size] = 0x0;
	doc.ParseInsitu(jsonBuffer);
	std::cout << "Parsing end" << std::endl;

	// prepare space for buffers. not loading all into memory for performance
	nBuffers = doc["buffers"].GetArray().Size();
	dataBuffers = new char*[nBuffers]();
	// load accessor and bufferView data in
	for (auto& accessor : doc["accessors"].GetArray()) {
		accessors.push_back({});
		saccessor& back = accessors.back();
		
		back.BVOffset = accessor["byteOffset"].GetUint();
		std::string typeS = accessor["type"].GetString();
		if(typeS == "SCALAR") {
			back.type = 0;
			back.typen = 1;
		} else if(typeS.rfind("VEC", 0)) {
			back.type = 1;
			back.typen = typeS[3]-'0';
		}
		back.componentType = accessor["componentType"].GetUint();
		back.count = accessor["count"].GetUint();
		
		rapidjson::Value& BV = doc["bufferViews"][accessor["bufferView"].GetInt()];

		if(BV.HasMember("byteOffset")) {
			back.byteOffset = BV["byteOffset"].GetUint();
		} else {
			back.byteOffset = 0;
		}
		
		back.byteLength = BV["byteLength"].GetUint();
		if(BV.HasMember("byteStride")) {
			back.byteOffset = BV["byteStride"].GetUint();
		} else {
			back.byteOffset = 0;
		}
		back.buffer = BV["buffer"].GetUint();
		std::cout <<"COCK"<< BV["buffer"].GetUint() << std::endl;

		switch(back.componentType) {
			case 5120: case 5121:
				back.componentByteSize = back.typen*sizeof(char);
				break;
			case 5122: case 5123:
				back.componentByteSize = back.typen*sizeof(short);
				break;
			case 5125:
				back.componentByteSize = back.typen*sizeof(int);
				break;
			case 5126:
				back.componentByteSize = back.typen*sizeof(float);
				break;
			default:
				std::cout << "UNEXPECTED DATA TYPE FOUND IN ACCESSOR."  << std::endl;
				break;
		}
	}

}
GLTFParser::~GLTFParser() {
	delete[] jsonBuffer;
	for(int x = 0; x < nBuffers; x++) {
		delete dataBuffers[x];
	}
	delete[] dataBuffers;
}

char* GLTFParser::returnDataBuffer(uint index) {
	if(!dataBuffers[index]) {
		rapidjson::Value& buff = doc["buffers"][index];
		int len = buff["byteLength"].GetInt();
		std::string URI = buff["uri"].GetString();
		std::string URIPath = path + "/" + URI;
		dataBuffers[index] = new char[len];

		std::ifstream file(URIPath, std::ios::binary);
		if (file.read(dataBuffers[index], len)) {
			std::cout << "Reading " << URI << " buffer successful!"<<std::endl;
		} else {
			std::cout << "Failed to read from file " << URI <<std::endl;
		}
	}
	return dataBuffers[index];
}


std::vector<Mesh> GLTFParser::getMeshes() {
	std::vector<Mesh> meshesVec;
	for(auto& meshJson : doc["meshes"].GetArray()) {
		if(meshJson["primitives"].GetArray().Size()>1){
			std::cout << "Warning "	 <<  filename << " contains a mesh with more than 1 primitive." << std::endl;
		}
		
		rapidjson::Value& data = meshJson["primitives"][0];
		int indicesAccessor = data["indices"].GetInt();
		
		saccessor& positionsAccessor = accessors[data["attributes"]["POSITION"].GetInt()];
		
		//for multiple accessors check if buffer is the same. otherwise add logic
		char* vertBuff = returnDataBuffer(positionsAccessor.buffer);

		//check if buffer data is interleaved
		//if its interleaved load data to mesh
		//otherwise merge the data

		
		
		/*
		meshesVec.push_back({});
		Mesh& mesh = meshesVec.back();
		char* meshVertBuff = mesh.allocateVertexBuffer(positionsAccessor.count, positionsAccessor.componentByteSize);
		if(positionsAccessor.byteStride == 0) {
			memcpy(meshVertBuff, vertBuff + positionsAccessor.byteOffset + positionsAccessor.BVOffset, positionsAccessor.byteLength);
		}*/
		
		//int positionsAccessor = data["attributes"]["NORMAL"].GetInt();

	}
	return meshesVec;
}


/*
GLTF::GLTF
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
}*/