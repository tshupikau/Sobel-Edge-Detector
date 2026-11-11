#pragma once
#include "UIElement.h"
#include <string>

class FileInputPanel : public UIElement
{
private:
	char path[1024] {};
	std::string status;
	bool loadClicked = false;
	void Draw() override;
public:
	FileInputPanel() : UIElement("File Input") {}

	bool isLoadRequested() const { return loadClicked; }
	const char* getPath() const { return path; }
	void setStatus(std::string s) { status = std::move(s); }
};