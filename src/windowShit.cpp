#include "buildConfig.h"
#include "windowShit.h"
#include "globals.h"




void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void mousePosCallback(GLFWwindow* window, double x, double y) {

}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void windowSizeCallback(GLFWwindow* window, int w, int h) {
    glfwGetFramebufferSize(window, MTN_XY(&globs.windowState.frameSize));
}






void initWindow() {

    MTN_ASSERT(glfwInit());

    glfwWindowHint(GLFW_MAXIMIZED, true);
    GLFWwindow *w = glfwCreateWindow(400, 400, MTN_PROJ_NAME, nullptr, nullptr);
    MTN_ASSERT(w);
    globs.windowState.window = w;

    // does this throw a fit?
    glfwMakeContextCurrent(w);
    glfwSwapInterval(1);



    glfwSetKeyCallback(w, keyCallback);
    glfwSetFramebufferSizeCallback(w, windowSizeCallback);
    glfwSetCursorPosCallback(w, mousePosCallback);
    glfwSetMouseButtonCallback(w, mouseButtonCallback);

    initGLCtx();
}



void updateWindow() {

    globs.windowState.shouldClose = glfwWindowShouldClose(globs.windowState.window);

    glfwPollEvents();
    glfwSwapBuffers(globs.windowState.window);
};








void GLLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char* message, const void* userParam) {

    char pref[] = "[GL MESSAGE]: ";
    //                                 null terminator included in pref len, not msg len
    char* str = ALLOC_ARR_BUMP(globs.frameArena, sizeof(pref) + length + 16, char);
    strcpy(str, pref);
    strcat(str, message);

    MTN_LOG(str);
};

void initGLCtx() {

    gladLoadGL(glfwGetProcAddress);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLLog, 0);
}