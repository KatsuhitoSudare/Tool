#include "HierarchyView.h"
#include"..\IMGUI\imgui.h"
#include"..\SceneManager\SceneManager.h"
#include"..\KaleidoScopeCollection\GameObject.h"
#include"InspecterView.h"
#include"GuiWindowManager.h"

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

			if (!ObjectArray)
			{
				ObjectArray = SceneManager::GetObjectArray();
			}

			for (auto obj : *ObjectArray)
			{
				if (ImGui::TreeNodeEx(obj->ObjectName.c_str(), ImGuiTreeNodeFlags_Leaf)) {

					if (ImGui::IsItemClicked())
					{
						GuiWindowManager::SetSelectObject((void*)obj);
					}

					ImGui::TreePop();
				}
			}	

			ImGui::End();
		}
	}
}