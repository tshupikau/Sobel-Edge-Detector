#pragma once
#include "IImageOperation.h"
#include "core/Image.h"

class ToGray : public IImageOperation
{
public:
	Image apply(const Image& input) const override;
};