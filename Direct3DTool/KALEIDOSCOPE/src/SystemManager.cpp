#include "SystemManager.h"
#include"cWindowManager.h"
#include"cDirect3D.h"
#include"ViewManager.h"

namespace KALEIDOSCOPE
{ 
	void SystemManager::Initialize()
	{
		//Win32�E�B���h�E�̍쐬
		cWindowManager::SetWindowSize(1980, 1080);
		cWindowManager::SetWindowTitle(L"KALEIDOSCOPE");
		cWindowManager::MakeWindow();
		//DirectX11�̏�����
		cDirect3D::Direct3DInit(cWindowManager::GetWindowHandole());

		//GUI��View��������
		GUI::ViewManager::Inititalize();

	}

	void SystemManager::ShutDown()
	{
		GUI::ViewManager::SutoDoun();
	}

	void SystemManager::MainLoop()
	{
		//���C�����[�v�̊J�n
		while (cWindowManager::ProcessMessage())
		{
			cDirect3D::ClearRenderTarget(0.4, 0.4, 0.4);




			GUI::ViewManager::Render();

			cDirect3D::SwapBuffuer();
		}
	}
}


