#include "buildConfig.h"
#include "external/GLAD/gl.h"
#include "RenderStructs.h"
#include "memory.h"
#include "external/stb_image/stb_image.h"


#if MTN_RENDER_API == MTN_GL





void bindTexture(Texture2d& t, s32 slot) {

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, t.renderID);
}





void Texture2d::load(
    Texture2d* tex, const char& src, int channelCount,
    TEXTURE_FILTER_MODE filter, TEXTURE_WRAP_MODE wrap) {

    MTN_ASSERT(tex);
    MTN_ASSERT(channelCount == 3 || channelCount == 4);


    *tex = Texture2d();
    tex->channels = channelCount;
    glGenTextures(1, &(tex->renderID));
    bindTexture(*tex, 0);


    // TEXTURE FILTER MODE
    // only allows for one mode for the whole texture
    // CLEANUP: check on that ^^^^
    if(filter == TEXTURE_FILTER_MODE::LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else if(filter == TEXTURE_FILTER_MODE::NEAREST) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    // TEXTURE WRAP
    if(wrap == TEXTURE_WRAP_MODE::CLAMP_TO_EDGE) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    } else if(wrap == TEXTURE_WRAP_MODE::REPEAT) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }



    // load and send data to tex
    stbi_set_flip_vertically_on_load(1);
    //CLEANUP: file channels is awful
    tex->data = stbi_load(&src, &tex->width, &tex->height, &tex->fileChannels, channelCount);
    MTN_ASSERT(tex->data);

    glTexImage2D(GL_TEXTURE_2D, 0,
        channelCount==3?GL_RGB8:GL_RGBA8, // texture color layout
        tex->width, tex->height, 0,
        channelCount==3?GL_RGB:GL_RGBA, // pixel data format
        GL_UNSIGNED_BYTE, // type per pix.
        tex->data); // buffer ptr
}










// bindings
void setRenderTarget();
void setShader();
void setVertexBuffer();
void setIndexBuffer();
void setRenderStage();

void clear();

#endif