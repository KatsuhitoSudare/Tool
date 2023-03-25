#include "SceneView.h"
#include"..\IMGUI\imgui.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		SceneView::SceneView()
		{
			WindowName = "Scene";
		}
		void SceneView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);
			ImGui::End();
		}
	}
}