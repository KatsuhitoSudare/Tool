#pragma once
#include "Window.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class GameView :public Window
		{
		public:
			GameView();
			void Update()override;
		};
	}
}


