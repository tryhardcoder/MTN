
#pragma once

#include "buildConfig.h"
#include "utils.h"






enum class GEO_LAYOUT_MEMBER {

    F3POS,
    F2UV,
    F3NORM
};

enum class IMAGE_LAYOUT {

    F1COLOR,
    F3COLOR,
    F4COLOR,
    F1DEPTH
};





struct IndexBuffer {
    u32 renderID;
    char* data = nullptr;
};

struct VertexBuffer {
    u32 VBRenderID = 0;
    char* data = nullptr;
    GEO_LAYOUT_MEMBER* layout = nullptr;

    // CLEANUP: are VAOS gl only?
    u32 VAORenderID = 0;
};

struct Mesh {
    IndexBuffer ib;
    VertexBuffer vb;
};

struct RenderTarget {
    u32 renderID = 0;
    IMAGE_LAYOUT* attachedLayouts = nullptr;
};

struct Texture {
    u32 renderID = 0;
    char* srcPath = nullptr;
    u32 width = 0;
    u32 height = 0;
    void* data = nullptr;
    IMAGE_LAYOUT layout = IMAGE_LAYOUT::F1COLOR;
};

struct Shader {
    u32 renderID = 0;
    char *srcPath = nullptr;
    GEO_LAYOUT_MEMBER* vertLayout = nullptr;
    IMAGE_LAYOUT* targetLayoutAttachments = nullptr;
};


struct RenderStage {
    Shader* shader = nullptr;
    RenderTarget* renderTarget = nullptr;
};
