#include "ProjectView.h"
#include"..\IMGUI\imgui.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		ProjectView::ProjectView()
		{
			WindowName = "Assets";
		}
		void ProjectView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);
			ImGui::End();
		}
	}
}