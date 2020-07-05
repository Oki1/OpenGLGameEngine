#include "opengl.hpp"
#include <iostream>

namespace swl {
struct color {
    unsigned char r{0}, g{0}, b{0}, a{0};
};

inline GLFWwindow* window = nullptr;

inline int initial_window_height = 100, initial_window_width = 160;
inline std::string initial_window_title = "untitled";
inline color background_color;

bool init();
void clear();
void updateScreen();
void update();
}

