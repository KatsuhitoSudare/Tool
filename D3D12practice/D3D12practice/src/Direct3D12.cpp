#include "Direct3D12.h"
#include"cWindowManager.h"

#pragma comment( lib, "d3d12.lib") 
#pragma comment( lib, "dxgi.lib")



Direct3D12::Direct3D12()
:m_pDevice(nullptr),
m_pFactory(nullptr),
m_pSwapChain(nullptr),
m_pAllocator(nullptr),
m_pCommandList(nullptr),
m_pQueue(nullptr),
m_pRtv(nullptr),
m_pFence(nullptr),
m_FenceVal(0)
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
	//�f�o�b�O���C���[���I����
	//�f�o�C�X�������O�ɂ���Ă����Ȃ��ƁA�f�o�C�X������ɂ���
	//�f�o�C�X�����X�Ƃ��Ă��܂��̂Œ���
	ID3D12Debug* debugLayer = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer)))) {
		debugLayer->EnableDebugLayer();
		debugLayer->Release();
	}
#endif
	
	HRESULT hr;
	//�t�@�N�g���̍쐬
#ifdef _DEBUG
	hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_pFactory));
	if (FAILED(hr))
	{
		return FALSE;
	}
#else
hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&m_pFactory));
if (FAILED(hr))
{
	return FALSE;
}
#endif // _DEBUG

//�f�o�C�X�̍쐬
	hr = D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL_12_1,
		IID_PPV_ARGS(&m_pDevice));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//�R�}���h�A���P�[�^�[�̍쐬
	hr = m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_pAllocator));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//�R�}���h���X�g�̍쐬
	hr = m_pDevice->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT,m_pAllocator,nullptr,IID_PPV_ARGS(&m_pCommandList));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//�R�}���h�L���[�̍쐬
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};

	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;//�^�C���A�E�g�Ȃ�
	cmdQueueDesc.NodeMask = 0;//�A�_�v�^�͈��
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = m_pDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_pQueue));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//�X���b�v�`�F�C���̍쐬
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

	//�t�F���X�̍쐬
	hr = m_pDevice->CreateFence(0,D3D12_FENCE_FLAG_NONE,IID_PPV_ARGS(&m_pFence));
	if (FAILED(hr))
	{
		return FALSE;
	}

	//�����_�[�^�[�Q�b�g�̍쐬
	m_pRtv = new RenderTergetView();
	m_pRtv->CreateRenderTerget(m_pSwapChain, 2);

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
	//�R�}���h�̋L�^���J�n����
	auto hr = m_pAllocator->Reset();
	if (FAILED(hr))
	{
		return;
	}
	hr = m_pCommandList->Reset(m_pAllocator, nullptr);
	if (FAILED(hr))
	{
		return;
	}
	//�X���b�v�`�F�C������J�����g�o�b�t�@���擾����
	auto bbIdx = m_pSwapChain->GetCurrentBackBufferIndex();

	// ���\�[�X�o���A�̐ݒ�.
	D3D12_RESOURCE_BARRIER barrier = {};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = m_pRtv->GetRTVResource(bbIdx);
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	// ���\�[�X�o���A.
	m_pCommandList->ResourceBarrier(1, &barrier);

	//�����_�[�^�[�Q�b�g�̃N���A
	float color[4] = { 0.6f,0.6f,0.6f,1.0 };
	m_pRtv->SetRenderTerget(m_pCommandList, bbIdx, color);

	// ���\�[�X�o���A�̐ݒ�.
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = m_pRtv->GetRTVResource(bbIdx);
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	// ���\�[�X�o���A.
	m_pCommandList->ResourceBarrier(1, &barrier);

	//�R�}���h���X�g�����
	hr = m_pCommandList->Close();
	if (FAILED(hr))
	{
		return;
	}
	//�R�}���h���X�g�̔z��
	ID3D12CommandList* list[] = { m_pCommandList };

	//�R�}���h�����s
	m_pQueue->ExecuteCommandLists(1,list);

	m_pQueue->Signal(m_pFence,++m_FenceVal);

	if (m_pFence->GetCompletedValue() != m_FenceVal)
	{
		auto event = CreateEvent(nullptr, false, false, nullptr);
		m_pFence->SetEventOnCompletion(m_FenceVal, event);

		WaitForSingleObject(event, INFINITE);

		CloseHandle(event);
	}

	m_pSwapChain->Present(1,0);
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
	COMSAFERELEASE(m_pFence);
	delete m_pRtv;
}
