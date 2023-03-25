#pragma once

#include "buildConfig.h"
#include "utils.h"
#include "RenderStructs.h"
#include "memory.h"


// res management
// void createRenderTarget();
void createTexture2d(
    Texture2d* tex, const char& src,
    TEXTURE_FILTER_MODE filter, TEXTURE_WRAP_MODE wrap,
    BumpAlloc* resourceBuff);


// bindings
void setRenderTarget();
void setShader();
void setVertexBuffer();
void setIndexBuffer();
void setRenderStage();

void clear();