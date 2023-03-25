#include "InspecterView.h"
#include"..\IMGUI\imgui.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		InspecterView::InspecterView()
		{
			WindowName = "InspecterView";
		}
		void InspecterView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);
			ImGui::End();
		}
	}
}