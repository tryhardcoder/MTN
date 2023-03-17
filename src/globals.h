#pragma once


#include "buildConfig.h"
#include "windowShit.h"
#include "memory.h"


struct Globs {

    BumpAlloc frameArena =      BumpAlloc(FRAME_ARENA_SIZE);
    BumpAlloc lifetimeArena =   BumpAlloc(LIFETIME_ARENA_SIZE);

    WindowState windowState =   WindowState();
};

extern Globs globs;