#pragma once
#include <GLFW/glfw3.h>
#include "Window.h"
#include "gui/FileInputPanel.h"
#include "gui/Texture.h"
#include "gui/ImGuiLayer.h"

class App 
{
private:
	Window window;
	ImGuiLayer uiLayer{ window.getWindow() };
public:
	void run();
	void update();
};