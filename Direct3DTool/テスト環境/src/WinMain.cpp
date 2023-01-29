#include<Windows.h>
#include"cSystemMain.h"


INT WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	KALEIDOSCOPE::cSystemMain::SystemInit();
	KALEIDOSCOPE::cSystemMain::MainLoop();
	return 0;
}