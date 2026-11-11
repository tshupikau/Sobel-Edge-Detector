#pragma once
#include "image.h"

class IImageFormat
{
public:
    virtual ~IImageFormat() = default;
    virtual bool canRead(const std::string& path) const = 0;
    virtual Image read(const std::string& path) const = 0;
};