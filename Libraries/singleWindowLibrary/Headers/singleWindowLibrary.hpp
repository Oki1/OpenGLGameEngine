#include "opengl.hpp"
#include <iostream>

namespace swl {
inline GLFWwindow* window = nullptr;

inline int initial_window_height = 100, initial_window_width = 160;
inline std::string initial_window_title = "untitled";
bool init();
}
