#include "HierarchyView.h"
#include"..\IMGUI\imgui.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		HierarchyView::HierarchyView()
		{
			WindowName = "Hierarchy";
		}
		void HierarchyView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);
			ImGui::End();
		}
	}
}