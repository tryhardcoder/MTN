#pragma once

#include "buildConfig.h"
#include "utils.h"
#include "rendering/RenderStructs.h"
#include "external/glm/matrix.hpp"


enum class ENTITY_FLAGS {

    NONE        = 0,
    SCRIPT      = 1 << 0,
    MESH        = 1 << 1
};



// TODO: pretty sure that all of the physics shit should be stored
// adjacent per param, that means entity pos should be a ptr?
// It may be better to copy over the mat before script runtime to keep
// the data near to the other shit being operated on
// (It would also require a copy back)
struct Entity;
typedef void (*EntityFunc)(Entity* e);
struct Entity {

    char* name;

    EntityFunc script = [](Entity* e){};
    Mesh* mesh = nullptr;
    b32 flags;
};