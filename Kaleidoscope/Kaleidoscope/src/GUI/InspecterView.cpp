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

			ImVec2 window_size = ImGui::GetWindowSize();
			ImGui::Text("Window size: (%.1f, %.1f)", window_size.x, window_size.y);

			void* pselect = GuiWindowManager::GetSelectObject();
			if (pselect != nullptr)
			{
				KALEIDOSCOPE::COLLECTION::GameObject* obj = static_cast<KALEIDOSCOPE::COLLECTION::GameObject*>(pselect);
				if (obj != nullptr)
				{
					ImGui::SetNextItemWidth(window_size.x * 0.33);
					ImGui::Text("position");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("x", &obj->transform.Pos.x, 0.01f);
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("y", &obj->transform.Pos.y, 0.01f);
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("z", &obj->transform.Pos.z, 0.01f);

					ImGui::Text("Rotate  ");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("x", &obj->transform.Rotate.x, 0.01f);
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("y", &obj->transform.Rotate.y, 0.01f);
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("z", &obj->transform.Rotate.z, 0.01f);

					ImGui::Text("Scale   ");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("x", &obj->transform.Scale.x, 0.01f);
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("y", &obj->transform.Scale.y, 0.01f);
					ImGui::SameLine();
					ImGui::SetNextItemWidth(window_size.x * 0.2);
					ImGui::DragFloat("z", &obj->transform.Scale.z, 0.01f);



					//if (ImGui::IsItemActive())
					//{
					//	float delta = ImGui::GetIO().MouseDelta.x; // マウスの移動量を取得する
					//	value += delta * 0.01f; // 数値を変更する
					//}
				}
			}
			ImGui::End();

			
		}
	}
}