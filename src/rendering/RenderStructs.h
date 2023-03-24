
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

enum class TEXTURE_FILTER_MODE {
    LINEAR,
    NEAREST
};

enum class TEXTURE_WRAP_MODE {
    CLAMP_TO_EDGE,
    REPEAT
};





struct IndexBuffer {
    u32 renderID;
    char* data = nullptr;
};

struct VertexBuffer {
    u32 VBRenderID = 0;
    char* data = nullptr;
    GEO_LAYOUT_MEMBER* layout = nullptr;

    // RES: are VAOS gl only?
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

struct Texture2d {

    int channels = 0;
    int width = 0;
    int height = 0;
    byte* data = nullptr;
    IMAGE_LAYOUT layout = IMAGE_LAYOUT::F1COLOR;
    u32 renderID = 0;

    //CLEANUP: both are purely metadata, consider removing?
    char* srcPath = nullptr;
    int fileChannels = 0;

    void load(Texture2d* tex, const char& src, int channelCount,
    TEXTURE_FILTER_MODE filter, TEXTURE_WRAP_MODE wrap);

    void bind();
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
