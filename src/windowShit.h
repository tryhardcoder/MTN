
#pragma once

#include "buildConfig.h"

#define GLFW_INCLUDE_NONE
#include "external/GLFW/glfw3.h"
#include "external/GLAD/gl.h"

#include "external/glm/vec2.hpp"



struct WindowState {


    // please don't fuck with this stuff, I feel like that shouldn't be too hard
    GLFWwindow* window = nullptr;
    bool shouldClose = false;
    glm::ivec2 frameSize = glm::ivec2();
};




// assumes that GLFW and GL have not been initialized, created ctx for both
// all info put into globs
void initWindow();

void initGLCtx();


// swaps framebuffer and polls for input
void updateWindow();


