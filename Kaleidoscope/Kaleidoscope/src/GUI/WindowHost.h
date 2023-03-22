#pragma once
#include<Windows.h>

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class WindowHost
		{
		public:
			static void InitializeGUI();
			static void UpdateGUI();
			static void RenderGUI();
			static void ShutDownGUI();
		private:
			static int HostWindowW, HostWindowH;
			static int HostWindowPosX, HostWindowPosY;
			static int TitleBerHeight;
		};
	}
}


