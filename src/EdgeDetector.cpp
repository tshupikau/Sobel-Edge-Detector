#include "EdgeDetector.h"

Image ImageProcessing::BGRtoGray(const Image& img)
{
    Image out(img.getWidth(), img.getHeight(), 1);

    for (int y = 0; y < img.getHeight(); ++y)
        for (int x = 0; x < img.getWidth(); ++x)
        {
            int r = img.at(x, y, 0), g = img.at(x, y, 1), b = img.at(x, y, 2);
            out.at(x, y) = (uint8_t)(0.299 * r + 0.587 * g + 0.114 * b);
        }

    return out;
}

Image ImageProcessing::conv2d(const Image& gray)
{
    const int w = gray.getWidth(), h = gray.getHeight();
    Image out(w, h, 1);

    for (int y = 1; y < h - 1; ++y)
        for (int x = 1; x < w - 1; ++x)
        {
            int gx = 0, gy = 0;
            for (int i = -1; i <= 1; ++i)
                for (int j = -1; j <= 1; ++j)
                {
                    const int v = gray.at(x + j, y + i);
                    const int k = (i + 1) * 3 + (j + 1);
                    gx += v * Gx[k];
                    gy += v * Gy[k];
                }
            const int mag = (int)std::sqrt(gx * gx + gy * gy);
            out.at(x, y) = (uint8_t)std::min(255, mag);
        }
    return out;
}