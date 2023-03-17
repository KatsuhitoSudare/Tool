#include<Windows.h>
#include"SystemManager.h"




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	KALEIDOSCOPE::SystemManager::Initialize();

	KALEIDOSCOPE::SystemManager::MainLoop();

	KALEIDOSCOPE::SystemManager::ShutDown();
}