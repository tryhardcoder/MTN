#include "buildConfig.h"

#include <iostream>
#include <assert.h>

#define GLFW_INCLUDE_NONE
#include "external/GLFW/include/GLFW/glfw3.h"
#include "external/GLAD/gl.h"

#include "windowShit.h"
#include "globals.h"
#include "utils.h"

#include "game/Entity.h"



Globs globs = Globs();

int main(int, char**) {

    initWindow();

    while(!globs.windowState.shouldClose) {

        glViewport(0, 0, MTN_XY(globs.windowState.frameSize));


        float x = (float)(std::sin(glfwGetTime()) + 1) / 2;
        glClearColor(x, x, x, x);
        glClear(GL_COLOR_BUFFER_BIT);


        globs.frameArena.clear();

        updateWindow();
    }



    return 0;
}