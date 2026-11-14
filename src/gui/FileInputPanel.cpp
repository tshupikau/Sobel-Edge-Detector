#include "FileInputPanel.h"
#include <iostream>
#include <fstream>
#include "Window.h"
#include "App.h"

#include "core/Image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <algorithm>
#include <GLFW/glfw3.h>


void FileInputPanel::Draw()
{
	bool enter = ImGui::InputText("##path", path, sizeof(path),
		ImGuiInputTextFlags_EnterReturnsTrue);
	ImGui::SameLine();
	loadClicked = ImGui::Button("Load") || enter;
}