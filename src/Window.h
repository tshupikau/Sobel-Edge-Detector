#pragma once
#include <GLFW/glfw3.h>
#include "Image.h"

class Window 
{
private:
	GLFWwindow* window { nullptr };
public:
	Window();

	void createWindow();

	GLFWwindow* getWindow() { return window; }
};