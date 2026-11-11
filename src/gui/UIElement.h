#pragma once
#include <string>

class UIElement
{
private:
	std::string title;
protected:
	virtual void Draw() = 0;
public:
	explicit UIElement(std::string title) : title(std::move(title)) {}
	void Render();
};