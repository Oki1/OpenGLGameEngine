#include "Header/vertexAttributeArray.hpp"
#include <iostream>
//i <3 u
void AttrArray::bindVAO() {
	glBindVertexArray(VAO);
}
/*void AttrArray::bindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}*/

void AttrArray::loadVAO() {
	// generate VAO=> vertex attribute array. stores many VBOS allowing us to render them all with binding and calling ti
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}
void AttrArray::enableVAA(int attrToEnable) {
	glEnableVertexAttribArray(attrToEnable);
}
void AttrArray::addData(int attrToConfigure, int size, GLenum type, bool normalized, int stride, void* offset) {
	glVertexAttribPointer(attrToConfigure, size, type, normalized, stride, (void*)offset);
}
void AttrArray::loadVBO(void* data, unsigned int datasize) {
	//VBO=> vertex buffer object-stores a large amount of vertices on the gpu
	// id conresponding to the buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);// from here on any buffer calls we make will be used to configure VBO(on GL_ARRAY_BUFFER target)
	glBufferData(GL_ARRAY_BUFFER, datasize, data, GL_STATIC_DRAW);
}
void AttrArray::loadEBO(void* data, unsigned int datasize) {
	// generates EBO=> element buffer object. Less pixels=> indicies. yes im too lazy to write real comments. fuck off
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, datasize, data, GL_STATIC_DRAW);
}