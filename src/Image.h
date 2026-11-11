#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "formats/bmp/bmp.h"

class Image;

namespace ImageProcessing
{
    Image BGRtoGray(const Image& img);
    Image conv2d(const Image& img);
}

class Image
{
private:
    int width = 0, height = 0, channels = 0;
    std::vector<uint8_t> pixels;

public:
    Image(int w, int h, int ch) : width(w), height(h), channels(ch), pixels(w * h * ch) {}

    uint8_t& at(int x, int y, int c = 0) { return pixels[(y * width + x) * channels + c]; }
    const uint8_t& at(int x, int y, int c = 0) const { return pixels[(y * width + x) * channels + c]; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getChannels() const { return channels; }
    bool isBottomUp() const { return height > 0; }

    void setPixels(std::vector<uint8_t> p);

    const std::vector<uint8_t>& getPixels() const { return pixels; }
};