#pragma once

#include "buildConfig.h"
#include "utils.h"
#include "Render.h"


// res management
// void createRenderTarget();
void createTexture(const char& src);

// bindings
void setRenderTarget();
void setShader();
void setVertexBuffer();
void setIndexBuffer();
void setRenderStage();

void clear();