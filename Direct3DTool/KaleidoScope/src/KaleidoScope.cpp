#include "KaleidoScope.h"
#include"cDirect3D.h"
#include"cWindowManager.h"


BOOL KaleidoScope::KaleidoScopeInit()
{
    cWindowManager::SetWindowSize(1280, 720);
    cWindowManager::SetWindowTitle(L"ƒ^ƒCƒgƒ‹");
    cWindowManager::MakeWindow();
    cDirect3D::Direct3DInit(cWindowManager::GetWindowHandole());
    



    return TRUE;
}

BOOL KaleidoScope::MainLoop()
{
    while (cWindowManager::ProcessMessage())
    {
        cDirect3D::ClearRenderTarget(0.7, 0.7, 0.7);



        cDirect3D::SwapBuffuer();
    }

    return 0;
}
