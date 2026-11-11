#pragma once
#include "Image.h" 

#include <GLFW/glfw3.h> 

class Texture
{
public:
    Texture() = default;
    ~Texture();

    Texture(const Texture&) = delete;             
    Texture& operator=(const Texture&) = delete;

    void load(const Image& img);

    GLuint id() const { return texId; }
    int width() const { return w; }
    int height() const { return h; }
    bool flipY() const { return flip; }
    bool empty() const { return texId == 0; }

private:
    GLuint texId = 0;
    int w = 0, h = 0;
    bool flip = false;
};