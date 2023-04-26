#include "InspecterView.h"
#include"..\IMGUI\imgui.h"
#include"GuiWindowManager.h"

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
			void* pselect = GuiWindowManager::GetSelectObject();
			if (pselect != nullptr)
			{
				KALEIDOSCOPE::COLLECTION::GameObject* obj = static_cast<KALEIDOSCOPE::COLLECTION::GameObject*>(pselect);
				if (obj != nullptr)
				{
					ImGui::DragFloat3("Position", &obj->transform.Pos.x, 0.01f);
					ImGui::DragFloat3("Rotate  ", &obj->transform.Rotate.x, 0.01f);
					ImGui::DragFloat3("Scale   ", &obj->transform.Scale.x, 0.01f);
				}
			}
			ImGui::End();
		}
        
	}
}