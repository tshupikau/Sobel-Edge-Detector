#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "bmp.h"

class Image;

namespace EdgeDetector 
{
    void BGRtoGray(Image& img);
    void conv2d(Image& img);
}

class Image
{
private:
    BMPFileHeader header;
    BMPInfoHeader infoHeader;
    BMPColorHeader colorHeader;
    std::ifstream image;
    std::vector<int> pixels;

    void readBFH();
    void readBIF();
    void readBCH();
    void readPixels();
    
    friend void EdgeDetector::BGRtoGray(Image& img);
    friend void EdgeDetector::conv2d(Image& img);

public:
    Image(const std::string& filename);
    ~Image();
    void save(char* filename);
};