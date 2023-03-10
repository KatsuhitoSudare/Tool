#include "cSystemMain.h"
#include"cDirect3D.h"
#include"cWindowManager.h"
#include"ImguiLib.h"
#include"VertexShader.h"
#include"PixelShader.h"


VertexShader* VS;
PixelShader* PS;


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
		IMGUILIB->ImguiCreateButton("Window", "button1", Message, Edge);

		//テスト用
		{
			VS->InitVertexShader(L"vs.hlsl", "vs_main", cDirect3D::GetDevice());
			PS->InitPixelShader(L"ps.hlsl", "ps_main", cDirect3D::GetDevice());
		}



		return TRUE;
	}

	

	BOOL cSystemMain::MainLoop()
	{
		float fl = 0.0f;
		IMGUILIB->ImguiCreateSliderF("Window","sli",&fl,0.0f,1.0f);

		while (cWindowManager::ProcessMessage())
		{
			cDirect3D::ClearRenderTarget(0.4, 0.4, 0.4);
			IMGUILIB->ImguiRender();


			cDirect3D::SwapBuffuer();
		}

		IMGUILIB->Shutdown();
		return 0;
	}
}


