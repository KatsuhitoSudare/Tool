#include "AssetsView.h"
#include"..\IMGUI\imgui.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		AssetsView::AssetsView()
		{
			WindowName = "Assets";
		}
		void AssetsView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);
			ImGui::End();
		}
	}
}