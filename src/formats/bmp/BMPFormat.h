#pragma once
#include "IImageFormat.h"

class BmpFormat : public IImageFormat
{
public:
    bool  canRead(const std::string& path) const override;
    Image read(const std::string& path) const override;
    //void  write(const std::string& path, const Image& img) const override;
};