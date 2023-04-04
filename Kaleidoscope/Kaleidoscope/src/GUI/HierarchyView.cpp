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
		}
		void HierarchyView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);

			ObjectArray = SceneManager::GetObjectArray();

			

			for (auto& obj : *ObjectArray)
			{
				if (ImGui::TreeNode(obj->ObjectName.c_str())) {
					ImGui::TreePop();
				}
				if (ImGui::IsItemHovered())
				{
					if (ImGui::BeginPopupContextItem("Menu")) {
						if (ImGui::MenuItem("Item 1")) {
							// Item 1���I�����ꂽ�Ƃ��̏���
						}
						if (ImGui::MenuItem("Item 2")) {
							// Item 2���I�����ꂽ�Ƃ��̏���
						}
						ImGui::EndPopup();
					}
				}
				
			}			

			ImGui::End();
		}
	}
}