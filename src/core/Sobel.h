#pragma once
#include "IImageOperation.h"

class Sobel : public IImageOperation
{
public:
	Image apply(const Image& input) const override;
};