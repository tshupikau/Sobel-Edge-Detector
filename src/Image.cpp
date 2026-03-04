#include "../include/Image.h"
#include "../include/bmp.h"
#include <iostream>
#include <fstream>

Image::Image(const std::string& filename) 
{
    image.open(filename, std::ios::binary);
    if (!image) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    readBFH();
    readBIF();

    readPixels();

}

Image::~Image() 
{
    if (image.is_open()) {
        image.close();
    }
}

void Image::readBFH() 
{
    image.read(reinterpret_cast<char*> (&header.bfType), 2);
    image.read(reinterpret_cast<char*> (&header.biSize), 4);
    image.read(reinterpret_cast<char*> (&header.bfReserved1), 2);
    image.read(reinterpret_cast<char*> (&header.bfReserved2), 2);
    image.read(reinterpret_cast<char*> (&header.bfOffBits), 4);
}

void Image::readBIF() 
{
    image.read(reinterpret_cast<char*> (&infoHeader.size), 4);
    image.read(reinterpret_cast<char*> (&infoHeader.width), 4);
    image.read(reinterpret_cast<char*> (&infoHeader.height), 4);
    image.read(reinterpret_cast<char*> (&infoHeader.planes), 2);
    image.read(reinterpret_cast<char*> (&infoHeader.bit_count), 2);
    image.read(reinterpret_cast<char*> (&infoHeader.compression), 4);
    image.read(reinterpret_cast<char*> (&infoHeader.size_image), 4);
    image.read(reinterpret_cast<char*> (&infoHeader.x_pixels_per_meter), 4);
    image.read(reinterpret_cast<char*> (&infoHeader.y_pixels_per_meter), 4);
    image.read(reinterpret_cast<char*> (&infoHeader.colors_used), 4);
    image.read(reinterpret_cast<char*> (&infoHeader.colors_important), 4);
}

void Image::readBCH() 
{
    image.read(reinterpret_cast<char*> (&colorHeader.red_mask), 4); //2 - bytes      
    image.read(reinterpret_cast<char*> (&colorHeader.green_mask), 4); //2 - bytes
    image.read(reinterpret_cast<char*> (&colorHeader.blue_mask), 4); //2 - bytes
    image.read(reinterpret_cast<char*> (&colorHeader.alpha_mask), 4); //2 - bytes
    image.read(reinterpret_cast<char*> (&colorHeader.color_space_type), 4); //2 - bytes
    image.read(reinterpret_cast<char*> (&colorHeader.unused), 4); //2 - bytes
}

void Image::readPixels() 
{
    std::vector<uint8_t> pixelsUint8(infoHeader.size_image);

    pixels.resize(infoHeader.size_image);
    image.seekg(header.bfOffBits);
    image.read(reinterpret_cast<char*>(pixelsUint8.data()), infoHeader.size_image);
    pixels.assign(pixelsUint8.begin(), pixelsUint8.end());
}

void Image::save(char* filename) 
{
    std::ofstream out(filename, std::ios::binary);
    
    out.write(reinterpret_cast<char*>(&header.bfType), 2);
    out.write(reinterpret_cast<char*>(&header.biSize), 4);
    out.write(reinterpret_cast<char*>(&header.bfReserved1), 2);
    out.write(reinterpret_cast<char*>(&header.bfReserved2), 2);
    out.write(reinterpret_cast<char*>(&header.bfOffBits), 4);

    out.write(reinterpret_cast<char*>(&infoHeader.size), 4);
    out.write(reinterpret_cast<char*>(&infoHeader.width), 4);
    out.write(reinterpret_cast<char*>(&infoHeader.height), 4);
    out.write(reinterpret_cast<char*>(&infoHeader.planes), 2);
    out.write(reinterpret_cast<char*>(&infoHeader.bit_count), 2);
    out.write(reinterpret_cast<char*>(&infoHeader.compression), 4);
    out.write(reinterpret_cast<char*>(&infoHeader.size_image), 4);
    out.write(reinterpret_cast<char*>(&infoHeader.x_pixels_per_meter), 4);
    out.write(reinterpret_cast<char*>(&infoHeader.y_pixels_per_meter), 4);
    out.write(reinterpret_cast<char*>(&infoHeader.colors_used), 4);
    out.write(reinterpret_cast<char*>(&infoHeader.colors_important), 4);

    out.write(reinterpret_cast<char*>(&colorHeader.red_mask), 4);
    out.write(reinterpret_cast<char*>(&colorHeader.green_mask), 4);
    out.write(reinterpret_cast<char*>(&colorHeader.blue_mask), 4);
    out.write(reinterpret_cast<char*>(&colorHeader.alpha_mask), 4);
    out.write(reinterpret_cast<char*>(&colorHeader.color_space_type), 4);
    out.write(reinterpret_cast<char*>(colorHeader.unused), 4 * 16);
    
    for (size_t i = 0; i < pixels.size(); ++i) 
    {
        uint8_t pixel = static_cast<uint8_t>(pixels[i]);
        out.put(pixel);
    }
}