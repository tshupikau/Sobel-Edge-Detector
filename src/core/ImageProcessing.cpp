#include "ImageProcessing.h"
#include <stdexcept>

std::vector<int> ImageProcessing::convolve(const Image& gray, const Kernel3& kernel)
{
    if (gray.getChannels() != 1)
        throw std::invalid_argument("convolve: expected 1 channel");

    const int w = gray.getWidth(), h = gray.getHeight();
    std::vector<int> out((size_t)w * h, 0);

    for (int y = 1; y < h - 1; ++y)
        for (int x = 1; x < w - 1; ++x)
        {
            int sum = 0;
            for (int i = -1; i <= 1; ++i)
                for (int j = -1; j <= 1; ++j)
                    sum += gray.at(x + j, y + i) * kernel[(i + 1) * 3 + (j + 1)];
            out[(size_t)y * w + x] = sum;
        }
    return out;
}