#include "../include/EdgeDetector.h"

void EdgeDetector::BGRtoGray(Image& img)
{
    std::vector<int> output(img.pixels.size(), 0);

    for (size_t i = 0; i < img.pixels.size(); i += 3) 
    {
        output[i] = 0.114 * img.pixels[i] + 0.587 * img.pixels[i + 1] + 0.299 * img.pixels[i + 2];
        output[i + 1] = 0.114 * img.pixels[i] + 0.587 * img.pixels[i + 1] + 0.299 * img.pixels[i + 2];
        output[i + 2] = 0.114 * img.pixels[i] + 0.587 * img.pixels[i + 1] + 0.299 * img.pixels[i + 2];
    }
    img.pixels = output;
}

void EdgeDetector::conv2d(Image& img) 
{
    std::vector<int> output = img.pixels;

    for (int n = 1; n < img.infoHeader.height - 1; n++)
    {
        for (int c = 1; c < img.infoHeader.width - 1; c++)
        {
            int gx = 0;
            int gy = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    for (int ch = 0; ch < 3; ch++)
                    {
                        int index = ((n + i) * img.infoHeader.width + (c + j)) * 3;

                        gx += img.pixels[index + ch] * Gx[(i + 1) * 3 + (j + 1)];
                        gy += img.pixels[index + ch] * Gy[(i + 1) * 3 + (j + 1)];
                    }
                }
            }
            int magnitude = std::sqrt(std::pow(gx, 2) + std::pow(gy, 2)) / 4;
            magnitude = std::min(255, magnitude);

            int pixelIndex = (n * img.infoHeader.width + c) * 3;
            output[pixelIndex] = magnitude;
            output[pixelIndex + 1] = magnitude;
            output[pixelIndex + 2] = magnitude;
        }
    }
    img.pixels = output;
}