#include "KS_WindowManager.h"
#include<ImguiLib.h>
#include<Windows.h>

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		void KS_WindowManager::Inititalize(ID3D11Device* device, ID3D11DeviceContext* context, HWND hWnd)
		{
			IMGUILIB->Initialize(hWnd,device,context);
			IMGUILIB->ImguiCreateWindowEX("wo", NoTitleBar);
		}

		void KS_WindowManager::Render()
		{
			IMGUILIB->ImguiRender();
		}

		void KS_WindowManager::ShutDown()
		{
			IMGUILIB->Shutdown();
		}
	}
}



