#include "Toolbar.h"
#include"..\IMGUI\imgui.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		Toolbar::Toolbar()
		{
			WindowName = "Toolbar";
		}
		void Toolbar::Update()
		{
			ImGui::Begin(WindowName.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar);

			ImGui::End();
		}
	}
}
