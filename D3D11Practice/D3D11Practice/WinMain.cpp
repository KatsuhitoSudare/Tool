#include"src/cWindowManager.h"
#include"src/Direct3D11/cDirect3D.h"
#include"src/ModelLoader.h"
#include"src/PMXLoader.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	cWindowManager::SetWindowSize(1920, 1080);
	cWindowManager::SetWindowTitle("Title");
	cWindowManager::MakeWindow();
	cDirect3D::Direct3DInit();


	while (cWindowManager::ProcessMessage())
	{
		cDirect3D::ClearRenderTarget(0.6,0.6,0.6);



		cDirect3D::SwapBuffuer();
	}


	return 0;
}