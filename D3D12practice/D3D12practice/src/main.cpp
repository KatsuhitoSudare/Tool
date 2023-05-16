#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include<iostream>
#include"cWindowManager.h"
#include"Direct3D12.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cWindowManager::SetWindowSize(1920, 1080);
	cWindowManager::SetWindowTitle("Direct3D12");
	cWindowManager::MakeWindow();
	if (!D3D12->Direct3D12Initialize())
	{
		printf("Ž¸”s");
		D3D12->Direct3D12ShutDown();
		return 0;
	}

	while (cWindowManager::ProcessMessage())
	{
		D3D12->RenderingStart();
	}

	D3D12->Direct3D12ShutDown();
	return 0;
	_CrtDumpMemoryLeaks();
}