#include<Windows.h>
#include"KaleidoScope.h"


INT WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	KaleidoScope::KaleidoScopeInit();

	KaleidoScope::MainLoop();

	return 0;
}