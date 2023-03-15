#pragma once


#include <cassert>
#include <iostream>

// define DEBUG for anything you only want in debug mode
#define DEBUG

#define MTN_LOG(x) (void)(std::cout << (x) << "\n")
#define MTN_ASSERT(x) assert(x)

#define MTN_PROJ_NAME "MTN - v0.0.0 - debug"

#define SCRATCH_ARENA_SIZE      10000000U
#define FRAME_ARENA_SIZE        10000000U
#define LIFETIME_ARENA_SIZE     10000000U

