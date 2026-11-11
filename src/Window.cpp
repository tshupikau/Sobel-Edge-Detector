#include "Window.h"
#include <GLFW/glfw3.h>

Window::Window()
{
	createWindow();
}

void Window::createWindow()
{
	glfwInit();

	window = glfwCreateWindow(1920, 1080, "My GLFW Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
}
