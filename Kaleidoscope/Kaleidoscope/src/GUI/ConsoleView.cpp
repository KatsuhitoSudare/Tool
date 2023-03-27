#include "ConsoleView.h"
#include"..\IMGUI\imgui.h"
#include"..\Collection\Collection.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		ConsoleView::ConsoleView()
		{
			WindowName = "Console";
		}
		void ConsoleView::Update()
		{
			static float Stac;
			static int countFrame;
			static int   FPS;
			Stac += Time::DeltaTime * 0.000001;
			countFrame++;
			if (Stac >= 1)
			{
				FPS = countFrame;
				countFrame = 0;
				Stac = 0;
			}

			ImGui::Begin(WindowName.c_str());

			ImGui::Text("%f", Time::DeltaTime);
			ImGui::Text("%d", FPS);

			ImGui::End();
		}
	}
}