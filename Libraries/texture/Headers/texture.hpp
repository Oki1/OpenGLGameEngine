#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace tex {
	class Texture {
	public:
		Texture(std::string name);
		inline int getHeight() {
			return height;
		}
		inline int getWidth() {
			return width;
		}
		unsigned int id;
		std::string path;
	private:
		int nrChannels, width, height;;
		unsigned char* data;
	};
}

#endif