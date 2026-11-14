#pragma once
#include <GLFW/glfw3.h>
#include "core/Image.h"

class Window 
{
private:
	GLFWwindow* window { nullptr };
public:
	Window();
	~Window();

	void createWindow();

	GLFWwindow* getWindow() { return window; }
};