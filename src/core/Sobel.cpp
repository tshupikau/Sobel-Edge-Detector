#include "Sobel.h"
#include "ImageProcessing.h"
#include "Kernels.h"

Image Sobel::apply(const Image& gray) const
{
    const std::vector<int> gx = ImageProcessing::convolve(gray, Kernels::Gx);
    const std::vector<int> gy = ImageProcessing::convolve(gray, Kernels::Gy);

    const int w = gray.getWidth(), h = gray.getHeight();
    Image out(w, h, 1);

    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
        {
            const size_t i = (size_t)y * w + x;
            const int mag = (int)std::lround(std::sqrt((double)gx[i] * gx[i] + (double)gy[i] * gy[i]));
            out.at(x, y) = (uint8_t)std::min(255, mag);
        }
    return out;
}