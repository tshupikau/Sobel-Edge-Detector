#include "Texture.h"
#include "core/Image.h"
#include <algorithm>
#include <vector>

Texture::~Texture()
{
    if (texId) glDeleteTextures(1, &texId);
}

void Texture::load(const Image& img)
{
    const int iw = img.getWidth(), ih = img.getHeight();
    const std::vector<uint8_t>& px = img.getPixels();
    if (iw <= 0 || ih <= 0 || px.empty()) return;

    const int ch = (int)(px.size() / ((size_t)iw * ih));
    auto clamp = [](int v) { return (unsigned char)std::clamp(v, 0, 255); };

    std::vector<unsigned char> rgba((size_t)iw * ih * 4);
    for (int i = 0; i < iw * ih; ++i)
    {
        const uint8_t* p = &px[(size_t)i * ch];
        if (ch == 1) rgba[i * 4 + 0] = rgba[i * 4 + 1] = rgba[i * 4 + 2] = clamp(p[0]);
        else
        {
            rgba[i * 4 + 0] = clamp(p[0]);
            rgba[i * 4 + 1] = clamp(p[1]);
            rgba[i * 4 + 2] = clamp(p[2]);
        }
        rgba[i * 4 + 3] = 255;
    }

    if (!texId) glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iw, ih, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());

    w = iw; h = ih; flip = img.isBottomUp();
}