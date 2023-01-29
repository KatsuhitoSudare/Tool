#include "cSystemMain.h"
#include"cDirect3D.h"
#include"cWindowManager.h"


namespace KALEIDOSCOPE
{
	BOOL cSystemMain::SystemInit()
	{
		cWindowManager::SetWindowSize(1280, 720);
		cWindowManager::SetWindowTitle(L"ƒ^ƒCƒgƒ‹");
		cWindowManager::MakeWindow();
		cDirect3D::Direct3DInit(cWindowManager::GetWindowHandole());
		return TRUE;
	}


	BOOL cSystemMain::MainLoop()
	{
		while (cWindowManager::ProcessMessage())
		{
			cDirect3D::ClearRenderTarget(0.4, 0.4, 0.4);



			cDirect3D::SwapBuffuer();
		}


		return 0;
	}
}


