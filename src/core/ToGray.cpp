#include "ToGray.h"
#include "Image.h"

Image ToGray::apply(const Image& input) const
{
    Image out(input.getWidth(), input.getHeight(), 1);

    for (int y = 0; y < input.getHeight(); ++y)
        for (int x = 0; x < input.getWidth(); ++x)
        {
            int r = input.at(x, y, 0), g = input.at(x, y, 1), b = input.at(x, y, 2);
            out.at(x, y) = (uint8_t)(0.299 * r + 0.587 * g + 0.114 * b);
        }

    return out;
}