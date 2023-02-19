#include"..\..\Direct3DTool\Win32API\src\cWindowManager.h"
#include"Direct3D12.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE,LPSTR,INT)
{
	cWindowManager::SetWindowSize(1280, 720);
	cWindowManager::SetWindowTitle(L"title");
	cWindowManager::MakeWindow();
	if (!Direct3D12::InitD3D12(cWindowManager::GetWindowHandole()))
	{
		return 0;
	};

	while (cWindowManager::ProcessMessage())
	{
		//更新処理はここに記述する

		Direct3D12::StartRecordCommand();

		Direct3D12::ClearRTV(0.4f, 0.4f, 0.4f);

		Direct3D12::ClearDSV();

		//描画処理は子kの間に記述する

		Direct3D12::EndRecordCommand();

		Direct3D12::RunCommand();

		Direct3D12::Present(1);
	}

	Direct3D12::ShutdownD3D12();
}