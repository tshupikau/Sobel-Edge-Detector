#include "UIElement.h"
#include "imgui.h"

void UIElement::Render()
{
    if (ImGui::Begin(title.c_str()))
        Draw();
    ImGui::End();
}