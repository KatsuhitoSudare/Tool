#pragma once
#include<Windows.h>
#include"Window.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class WindowHost : public Window
		{
		public:
			WindowHost();
			void Update()override;
		private:

		};
	}
}


