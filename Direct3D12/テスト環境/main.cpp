#include"..\..\Direct3DTool\Win32API\src\cWindowManager.h"
#include"Direct3D12.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE,LPSTR,INT)
{
	cWindowManager::SetWindowSize(1280, 720);
	cWindowManager::SetWindowTitle(L"title");
	cWindowManager::MakeWindow();
	if (!Direct3D12::InitD3D12(cWindowManager::GetWindowHandole()))
	{
		return 0;
	};

	while (cWindowManager::ProcessMessage())
	{

	}
}