cmake_minimum_required(VERSION 3.12.0)
project(MTN VERSION 0.1.0)

include(CTest)
enable_testing()






# MAKE PROJECT SETTINGS ==================================================

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
    )

add_executable(MTN ${SOURCES})
include_directories(src/)
include_directories(external/)

# MAKE PROJECT SETTINGS ==================================================




# ADD LIBS ==============================================================================

add_library(LibsModule external/GLAD/gl.c)

add_subdirectory(external/GLFW)
include_directories(external/GLFW/include)
target_link_libraries(LibsModule glfw ${GLFW_LIBRARIES})

add_subdirectory(external/glm)
target_link_libraries(LibsModule glm)

target_link_libraries(MTN LibsModule)

# ADD LIBS ==============================================================================



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
