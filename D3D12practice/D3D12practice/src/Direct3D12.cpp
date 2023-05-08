#include "Direct3D12.h"
#include"cWindowManager.h"

#pragma comment( lib, "d3d12.lib") 
#pragma comment( lib, "dxgi.lib")

#define COMSAFERELEASE(o){if(o != nullptr){o->Release();};}

Direct3D12::Direct3D12()
:m_pDevice(nullptr),
m_pFactory(nullptr),
m_pSwapChain(nullptr)
{}

Direct3D12* Direct3D12::GetInstatnce()
{
	if (!s_pInstance)
	{
		s_pInstance = new Direct3D12();
	}

	return s_pInstance;
}

void Direct3D12::Direct3D12ShutDown()
{
	if (s_pInstance != nullptr)
	{
		delete s_pInstance;
	}
}

BOOL Direct3D12::Direct3D12Initialize()
{
	//デバイスの作成
	auto hr = D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL_12_1,
		IID_PPV_ARGS(&m_pDevice));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//ファクトリの作成
	hr = CreateDXGIFactory(IID_PPV_ARGS(&m_pFactory));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//コマンドアロケーターの作成
	hr = m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_pAllocator));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//コマンドリストの作成
	hr = m_pDevice->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT,m_pAllocator,nullptr,IID_PPV_ARGS(&m_pCommandList));
	if (FAILED(hr))
	{
		return FALSE;
	}


	return TRUE;
}

Direct3D12::~Direct3D12()
{
	COMSAFERELEASE(m_pDevice);
	COMSAFERELEASE(m_pFactory);
	COMSAFERELEASE(m_pSwapChain);
}
