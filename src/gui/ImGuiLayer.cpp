#include "ImGuiLayer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "formats/bmp/BMPFormat.h"

ImGuiLayer::ImGuiLayer(GLFWwindow* window)
	: window(window)
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void ImGuiLayer::beginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::drawUI()
{
	fileInputPanel.Render();

	if (fileInputPanel.isLoadRequested())
	{
		if (!std::ifstream(fileInputPanel.getPath()))
		{
			fileInputPanel.setStatus("File not found");
		}
		else
		{
			BmpFormat bmp;
			Image src = bmp.read(fileInputPanel.getPath());
			Image gray = ImageProcessing::BGRtoGray(src);
			Image sobel = ImageProcessing::conv2d(gray);

			srcTex.load(src);
			edgesTex.load(sobel);
		}
	}

	ImGui::SetNextWindowPos(ImVec2(20, 150), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);

	originalImagePanel.Render();

	ImGui::SetNextWindowPos(ImVec2(540, 150), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);

	edgesImagePanel.Render();
	ImGui::Render();

	int w, h;
	glfwGetFramebufferSize(this->window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}