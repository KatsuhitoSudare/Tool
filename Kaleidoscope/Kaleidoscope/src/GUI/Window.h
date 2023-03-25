#pragma once
#include<string>
using std::string;

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class Window
		{
		public:
			Window() {};
			~Window() {};
			virtual void Update() {};
		protected:
			bool   CloseButton;
			string WindowName;
		};
	}
}
