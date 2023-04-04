#include "HierarchyView.h"
#include"..\IMGUI\imgui.h"
#include"..\SceneManager\SceneManager.h"
#include"..\KaleidoScopeCollection\GameObject.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		HierarchyView::HierarchyView()
		{
			WindowName = "Hierarchy";
			ObjectArray = SceneManager::GetObjectArray();
		}
		void HierarchyView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);

			for (auto& obj : *ObjectArray)
			{
				ImGui::Text(obj->ObjectName.c_str());
			}

			ImGui::End();
		}
	}
}