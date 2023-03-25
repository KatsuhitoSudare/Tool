#pragma once
#include "Window.h"


namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class SceneView :public Window
		{
		public:
			SceneView();
			void Update()override;
		};
	}
}


