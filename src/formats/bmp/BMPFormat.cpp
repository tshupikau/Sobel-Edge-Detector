#include "BmpFormat.h"
#include "bmp.h"
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <vector>

struct Rgb { uint8_t r, g, b; };

template <typename T>
T readStruct(std::istream& f)
{
    T value{};
    f.read(reinterpret_cast<char*>(&value), sizeof(T));
    return value;
}

static int rowStride(int width, int bitsPerPixel)
{
    return ((width * bitsPerPixel + 31) / 32) * 4;
}

std::vector<Rgb> readPalette(std::istream& f, const BMP::InfoHeader & info)
{
    const int count = info.colors_used ? (int)info.colors_used : 256;
    std::vector<uint8_t> raw((size_t)count * 4);

    f.seekg(sizeof(BMP::FileHeader) + info.size);
    f.read(reinterpret_cast<char*>(raw.data()), raw.size());

    std::vector<Rgb> palette(count);
    for (int i = 0; i < count; ++i)
        palette[i] = { raw[i * 4 + 2], raw[i * 4 + 1], raw[i * 4 + 0] };
    return palette;
}

static std::vector<uint8_t> readPixels(std::istream& f, int width, int height, int bpp,
    bool bottomUp, const std::vector<Rgb>& palette)
{
    std::vector<uint8_t> row(rowStride(width, bpp));
    std::vector<uint8_t> pixels((size_t)width * height * 3);
    const int step = bpp / 8;

    for (int r = 0; r < height; ++r)
    {
        f.read(reinterpret_cast<char*>(row.data()), row.size());

        const int y = bottomUp ? (height - 1 - r) : r;
        uint8_t* dst = &pixels[(size_t)y * width * 3];

        for (int x = 0; x < width; ++x)
        {
            Rgb c;
            if (bpp == 8)
            {
                const size_t idx = row[x];
                c = idx < palette.size() ? palette[idx] : palette[0];
            }
            else
            {
                const uint8_t* p = &row[x * step];
                c = { p[0], p[1], p[2] };           
            }
            dst[x * 3 + 0] = c.r;
            dst[x * 3 + 1] = c.g;
            dst[x * 3 + 2] = c.b;
        }
    }
    return pixels;
}

bool BmpFormat::canRead(const std::string& path) const
{
    std::ifstream file(path, std::ios::binary);
    char sig[2]{};
    file.read(sig, 2);
    return file && std::memcmp(sig, "BM", 2) == 0;
}

Image BmpFormat::read(const std::string& path) const 
{
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("Cannot open file: " + path);
    file.exceptions(std::ios::failbit | std::ios::badbit);

    const auto fileHeader = readStruct<BMP::FileHeader>(file);
    const auto infoHeader = readStruct<BMP::InfoHeader>(file);

    file.seekg(fileHeader.bfOffBits);

	int32_t width = infoHeader.width;
	int32_t height = infoHeader.height;
    uint16_t bitCount = infoHeader.bit_count;

    const auto palette = (bitCount == 8) ? readPalette(file, infoHeader) : std::vector<Rgb>{};

    file.seekg(fileHeader.bfOffBits);

    Image img(width, height, 3);
    img.setPixels(readPixels(file, width, height, bitCount, height < 0, palette));
    return img;
}

