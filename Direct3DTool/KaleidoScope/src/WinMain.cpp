#include<Windows.h>
#include"cWindowManager.h"
#include"cDirect3D.h"
#include"ImguiLib.h"
#include"GameObject.h"




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//Win32�E�B���h�E�̍쐬
	cWindowManager::SetWindowSize(1980,1080);
	cWindowManager::SetWindowTitle(L"KALEIDOSCOPE");
	cWindowManager::MakeWindow();
	//DirectX11�̏�����
	cDirect3D::Direct3DInit(cWindowManager::GetWindowHandole());

	GameObject gameobject;
	gameobject.Init();


	//���C�����[�v�̊J�n
	while (cWindowManager::ProcessMessage())
	{
		cDirect3D::ClearRenderTarget(0.4, 0.4, 0.4);

		gameobject.Draw();

		cDirect3D::SwapBuffuer();
	}

}