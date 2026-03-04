#pragma once
#include <vector>
#include "Image.h"

namespace EdgeDetector
{
    std::vector<int> Gx = {
         -1, 0, 1 ,
         -2, 0, 2 ,
         -1, 0, 1 
    };

    std::vector<int> Gy = {
         1, 2, 1 ,
         0, 0, 0 ,
        -1, -2, -1 
    };

    void BGRtoGray(Image& img);

    void conv2d(Image& img);
}