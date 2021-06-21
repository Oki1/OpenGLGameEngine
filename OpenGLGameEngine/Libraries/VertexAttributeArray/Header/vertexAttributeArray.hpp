#pragma once
#include <glad/glad.h>
class AttrArray {
public:
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	void enableVAA(int attrToEnable);
	void loadVBO(void* data, unsigned int datasize);
	void loadEBO(void* data, unsigned int datasize);
	void addData(int attrToConfigure, int size, GLenum type, bool normalized, int stride, void* offset);
	void loadVAO();
	//void bindEBO();
	void bindVAO();
	void unbindVAO();
};