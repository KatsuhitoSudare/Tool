#pragma once
#include<vector>
#include"Window.h"
#include"WindowHost.h"


namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class GuiWindowManager
		{
		public:
			static void InitializeGuiWindowAll();
			static void UpdateGuiWindowAll();
			static void RenderGuiWindowAll();
			static void ShutDownGuiWindowAll();
		private:
			static void ImGuiInit();
			static inline std::vector<Window*> WindowArray;
		};
	}
}



