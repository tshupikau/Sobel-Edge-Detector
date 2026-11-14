#pragma once
#include "gui/UIElement.h"
#include "gui/Texture.h"

class ImagePanel : public UIElement
{
public:
	ImagePanel(std::string title, const Texture& tex)
		: UIElement(std::move(title)), tex(tex) {}
private:
	const Texture& tex;
	
	void Draw() override;
	void DrawImageFit(const Texture& t);
};