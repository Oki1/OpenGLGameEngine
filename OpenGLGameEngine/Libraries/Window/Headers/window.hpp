#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
namespace wnd {
	struct color {
		unsigned char r{ 0 }, g{ 255 }, b{ 0 }, a{ 255 };
	};

	inline GLFWwindow* window;
	inline int initial_width = 800,  initial_height = 600;
	inline std::string initial_title = "didnt set a name you retard";
	inline color background_color;


	void clear();
	bool init();
	void updateScreen();
};