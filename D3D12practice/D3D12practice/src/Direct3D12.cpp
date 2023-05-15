#include "Direct3D12.h"
#include"cWindowManager.h"

#pragma comment( lib, "d3d12.lib") 
#pragma comment( lib, "dxgi.lib")



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
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	//デバイス生成時前にやっておかないと、デバイス生成後にやると
	//デバイスがロスとしてしまうので注意
	ID3D12Debug* debugLayer = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer)))) {
		debugLayer->EnableDebugLayer();
		debugLayer->Release();
	}
#endif
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
	hr = CreateDXGIFactory2(0,IID_PPV_ARGS(&m_pFactory));
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

	//コマンドキューの作成
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};

	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;//タイムアウトなし
	cmdQueueDesc.NodeMask = 0;//アダプタは一つ
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = m_pDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_pQueue));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//スワップチェインの作成
	UINT w, h;
	cWindowManager::GetWindowSize(&w, &h);

	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	swapchainDesc.Width = w;
	swapchainDesc.Height = h;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = false;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2;
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	hr = m_pFactory->CreateSwapChainForHwnd
	(
		m_pQueue,
		cWindowManager::GetWindowHandole(),
		&swapchainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&m_pSwapChain
	);
	//レンダーターゲットの作成
	m_pRtv = new RenderTergetView();

	return TRUE;
}

ID3D12Device* Direct3D12::GetDevice()
{
	return m_pDevice;
}

IDXGISwapChain4* Direct3D12::GetSwapChain()
{
	return m_pSwapChain;
}

void Direct3D12::RenderingStart()
{
	m_pAllocator->Reset();

	auto bbIdx = m_pSwapChain->GetCurrentBackBufferIndex();

	m_pCommandList->OMSetRenderTargets(1, );

}

ID3D12GraphicsCommandList* Direct3D12::GetCommandlist()
{
	return m_pCommandList;
}

Direct3D12::~Direct3D12()
{
	COMSAFERELEASE(m_pDevice);
	COMSAFERELEASE(m_pFactory);
	COMSAFERELEASE(m_pSwapChain);
	COMSAFERELEASE(m_pCommandList);
	COMSAFERELEASE(m_pAllocator);
	COMSAFERELEASE(m_pQueue);
	delete m_pRtv;
}
