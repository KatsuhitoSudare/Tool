#pragma once
#include "Window.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class ConsoleView :public Window
		{
		public:
			ConsoleView();
			void Update()override;
		};
	}
}



