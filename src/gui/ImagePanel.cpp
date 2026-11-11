#include "ImagePanel.h"
#include "Texture.h"

#include <algorithm>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void ImagePanel::Draw()
{
	DrawImageFit(tex);
}

void ImagePanel::DrawImageFit(const Texture& t)
{
	ImVec2 avail = ImGui::GetContentRegionAvail();
	if (t.empty() || avail.x <= 0 || avail.y <= 0)
	{
		ImGui::TextDisabled("No image");
		return;
	}
	float s = std::min(avail.x / t.width(), avail.y / t.height());
	ImVec2 uv0 = t.flipY() ? ImVec2(0, 1) : ImVec2(0, 0);
	ImVec2 uv1 = t.flipY() ? ImVec2(1, 0) : ImVec2(1, 1);
	ImGui::Image((ImTextureID)(intptr_t)t.id(),
		ImVec2(t.width() * s, t.height() * s), uv0, uv1);
}