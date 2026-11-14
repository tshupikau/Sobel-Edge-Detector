#pragma once
#include <memory>
#include <string>
#include "core/Image.h"

class IImageOperation
{
public:
    virtual Image apply(const Image& input) const = 0;
};