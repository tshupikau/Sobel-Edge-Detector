#pragma once
#include "Texture.h"

#include "FileInputPanel.h"
#include "ImagePanel.h"

class ImGuiLayer
{
private:
	Texture srcTex, edgesTex;
	FileInputPanel fileInputPanel;
	GLFWwindow* window{ nullptr };

	ImagePanel originalImagePanel {"Original", srcTex};
	ImagePanel edgesImagePanel {"Edges", edgesTex};

public:
	ImGuiLayer(GLFWwindow* window);
	~ImGuiLayer();

	void beginFrame();
	void drawUI();
};