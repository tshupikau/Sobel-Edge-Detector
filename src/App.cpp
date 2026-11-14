
#include "App.h"
#include "Window.h"

#include <GLFW/glfw3.h>
#include <algorithm>

void App::update()
{
	glfwPollEvents();

	uiLayer.beginFrame();
	uiLayer.drawUI();

	glfwSwapBuffers(window.getWindow());
}

void App::run() 
{
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		update();
	}
}