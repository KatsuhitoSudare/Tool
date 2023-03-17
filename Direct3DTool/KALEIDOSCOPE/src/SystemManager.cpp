#include "SystemManager.h"
#include"cWindowManager.h"
#include"cDirect3D.h"
#include"ViewManager.h"

namespace KALEIDOSCOPE
{ 
	void SystemManager::Initialize()
	{
		//Win32ウィンドウの作成
		cWindowManager::SetWindowSize(1980, 1080);
		cWindowManager::SetWindowTitle(L"KALEIDOSCOPE");
		cWindowManager::MakeWindow();
		//DirectX11の初期化
		cDirect3D::Direct3DInit(cWindowManager::GetWindowHandole());

		//GUIのViewを初期化
		GUI::ViewManager::Inititalize();

	}

	void SystemManager::ShutDown()
	{
		GUI::ViewManager::SutoDoun();
	}

	void SystemManager::MainLoop()
	{
		//メインループの開始
		while (cWindowManager::ProcessMessage())
		{
			cDirect3D::ClearRenderTarget(0.4, 0.4, 0.4);




			GUI::ViewManager::Render();

			cDirect3D::SwapBuffuer();
		}
	}
}


