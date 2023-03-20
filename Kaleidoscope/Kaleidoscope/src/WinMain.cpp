#include"Win32/Win32Window.h"
using namespace KALEIDOSCOPE::WINDOW;



INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Win32Window::SetWindowSize(1920, 1080);
	Win32Window::SetWindowTitle(L"KALEIDOSCOPE");
	Win32Window::MakeWindow();

	while (Win32Window::ProcessMessage())
	{




	}

	return 0;
}