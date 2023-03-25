#include "GameView.h"
#include"..\IMGUI\imgui.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		GameView::GameView()
		{
			WindowName = "Game";
		}
		void GameView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);
			ImGui::End();
		}
	}
}
