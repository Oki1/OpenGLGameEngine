#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>

#include <string>

enum texType { DIFFUSE, SPECULAR};
class Texture {
public:
	Texture(std::string name, bool flip = false);
	void bindTex(GLenum textureUnit);
	inline int getHeight() {
		return height;
	}
	inline int getWidth() {
		return width;
	}
	unsigned int id;
	texType type;
	std::string texturePath = "Resources/Textures/";
	std::string path;
private:
	int nrChannels, width, height;;
	unsigned char* data;
};

#endif