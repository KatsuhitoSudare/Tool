#include<Windows.h>
#include"cWindowManager.h"
#include"cDirect3D.h"
#include"ImguiLib.h"
#include"GameObject.h"




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//Win32ウィンドウの作成
	cWindowManager::SetWindowSize(1980,1080);
	cWindowManager::SetWindowTitle(L"KALEIDOSCOPE");
	cWindowManager::MakeWindow();
	//DirectX11の初期化
	cDirect3D::Direct3DInit(cWindowManager::GetWindowHandole());

	GameObject gameobject;
	gameobject.Init();


	//メインループの開始
	while (cWindowManager::ProcessMessage())
	{
		cDirect3D::ClearRenderTarget(0.4, 0.4, 0.4);

		gameobject.Draw();

		cDirect3D::SwapBuffuer();
	}

}