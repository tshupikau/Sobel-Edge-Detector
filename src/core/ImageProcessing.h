#pragma once
#include <array>
#include <vector>
#include "core/Image.h"

namespace ImageProcessing
{
    using Kernel3 = std::array<int, 9>;
    std::vector<int> convolve(const Image& gray, const Kernel3& kernel);
}