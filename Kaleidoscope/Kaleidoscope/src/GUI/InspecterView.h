#pragma once
#include "Window.h"
#include"..\KaleidoScopeCollection\GameObject.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class InspecterView :public Window
		{
		public:
			InspecterView();
			void Update()override;
			void* SelectObject;
		};
	}
}




