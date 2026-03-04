#include <iostream>
#include <fstream>
#include <cmath>
#include "../include/Image.h"

int main(int argc, char* argv[])
{
    Image img(argv[1]);
    EdgeDetector::conv2d(img);
    img.save(argv[2]);
}
