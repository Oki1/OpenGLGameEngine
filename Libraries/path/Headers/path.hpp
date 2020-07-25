#ifndef path_hpp
#define path_hpp

#include <string>

#ifdef __APPLE__
	inline std::string resourcePath = "../Resources/";
	#else
		inline std::string resourcePath = "Resources/";
#endif

	inline std::string shaderPath = resourcePath + "Shaders/";
	inline std::string texturePath = resourcePath + "Textures/";


#endif /* path_hpp */
