#pragma once


#include <cassert>
#include <iostream>

// define DEBUG for anything you only want in debug mode
// TODO: hook into cmake
#define DEBUG

// Render API def
#define MTN_RENDER_API MTN_GL
#define MTN_GL 0

#define MTN_LOG(x) (void)(std::cout << (x) << "\n")
#define MTN_ASSERT(x) assert(x)

#define MTN_PROJ_NAME "MTN - v0.0.0 - debug"

#define RES_ARENA_SIZE          10000000U
#define FRAME_ARENA_SIZE        10000000U
#define LIFETIME_ARENA_SIZE     10000000U

