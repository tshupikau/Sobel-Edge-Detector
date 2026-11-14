#include "Image.h"
#include <iostream>
#include <fstream>

void Image::setPixels(std::vector<uint8_t> p)
{
    if (p.size() != (size_t)getWidth() * getHeight() * getChannels())
        throw std::invalid_argument("Image::setPixels: wrong buffer size");
    pixels = std::move(p);
}