#include "cSystemMain.h"
#include"cDirect3D.h"
#include"cWindowManager.h"
#include"ImguiLib.h"

namespace KALEIDOSCOPE
{
	void Message()
	{
		MessageBox(cWindowManager::GetWindowHandole(), L"わーい", L"result", MB_ICONINFORMATION);
	}


	BOOL cSystemMain::SystemInit()
	{
		cWindowManager::SetWindowSize(1280, 720);
		cWindowManager::SetWindowTitle(L"タイトル");
		cWindowManager::MakeWindow();
		cDirect3D::Direct3DInit(cWindowManager::GetWindowHandole());
		IMGUILIB->Initialize(cWindowManager::GetWindowHandole(), cDirect3D::GetDevice(), cDirect3D::GetContext());
		IMGUILIB->ImguiCreateWindow("Window");
		IMGUILIB->CreateButton("Window", "button1", Message, Edge);


		return TRUE;
	}

	

	BOOL cSystemMain::MainLoop()
	{
		while (cWindowManager::ProcessMessage())
		{
			cDirect3D::ClearRenderTarget(0.4, 0.4, 0.4);
			IMGUILIB->RenderImgui();


			cDirect3D::SwapBuffuer();
		}

		IMGUILIB->Shutdown();
		return 0;
	}
}


