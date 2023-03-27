#include<Windows.h>
#include"SystemManager.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//インスタンスを生成
	KALEIDOSCOPE::SYSTEM::SystemManager Manager;

	Manager.SystemInitialize();

	Manager.SystemRunning();

	Manager.SystemShutDown();

	return 0;
}