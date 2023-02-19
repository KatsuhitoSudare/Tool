#include "Direct3D12.h"

BOOL Direct3D12::InitD3D12(HWND _hWnd)
{
#if defined(DEBUG) || defined(_DEBUG)
    {
        ComPtr<ID3D12Debug> debug;
        auto hr = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddressOf()));

        // �f�o�b�O���C���[��L����.
        if (SUCCEEDED(hr))
        {
            debug->EnableDebugLayer();
        }
    }
#endif

    HRESULT hr = S_OK;
	UINT         numModes = 0;
	DXGI_MODE_DESC* DisplayMode = nullptr;
	unsigned int numerator = 60;			// ���q
	unsigned int denominator = 1;			// ����
	RECT                rect;
	GetClientRect(_hWnd, &rect);
	UINT m_CWindowW = (UINT)(rect.right - rect.left);
	UINT m_CWindowH = (UINT)(rect.bottom - rect.top);
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,					// Windows Advanced Rasterizer
        D3D_DRIVER_TYPE_REFERENCE,
        D3D_DRIVER_TYPE_SOFTWARE,
    };

    unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

    //�t�@�N�g���[�̍쐬
    ComPtr<IDXGIFactory> factory = nullptr;
    hr = CreateDXGIFactory(IID_PPV_ARGS(factory.GetAddressOf()));
    if(FAILED(hr))
    {
        return FALSE;
    }

    //���ڂ���Ă���r�f�I�J�[�h���擾
    ComPtr<IDXGIAdapter> adaptaer;
    hr = factory->EnumAdapters(0, adaptaer.GetAddressOf());
    if(FAILED(hr))
    {
        return FALSE;
    }

    //�r�f�I�J�[�h���烂�j�^�[���擾
    ComPtr<IDXGIOutput> output;
    hr = adaptaer->EnumOutputs(0, output.GetAddressOf());
    if (FAILED(hr))
    {
        return FALSE;
    }

    //���j�^�[�̏ڍ׏����擾
    hr = output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
    if (FAILED(hr))
    {
        return FALSE;
    }

    DisplayMode = new DXGI_MODE_DESC[numModes];
    if (!DisplayMode) {
        return FALSE;
    }

    hr = output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, DisplayMode);
    if (FAILED(hr))
    {
        return FALSE;
    }

    for (unsigned int i = 0; i < numModes; i++) {
        if (DisplayMode[i].Width == m_CWindowW) {
            if (DisplayMode[i].Height == m_CWindowH) {
                numerator = DisplayMode[i].RefreshRate.Numerator;
                denominator = DisplayMode[i].RefreshRate.Denominator;
            }
        }
    }


    //�f�o�C�X�̍쐬
    hr = D3D12CreateDevice(adaptaer.Get(), D3D_FEATURE_LEVEL_11_1, IID_PPV_ARGS(m_pDevice.GetAddressOf()));
    if (FAILED(hr))
    {
        return FALSE;
    }

    //�R�}���h�L���[�̍쐬
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.NodeMask = 0;
    hr = m_pDevice->CreateCommandQueue(&desc,IID_PPV_ARGS(m_pQueue.GetAddressOf()));
    if (FAILED(hr))
    {
        return FALSE;
    }


    // �X���b�v�`�F�C���̐ݒ�.
    {
        // �X���b�v�`�F�C���̐ݒ�.
        DXGI_SWAP_CHAIN_DESC desc = {};
        desc.BufferDesc.Width = m_CWindowW;
        desc.BufferDesc.Height = m_CWindowH;
        desc.BufferDesc.RefreshRate.Numerator = numerator;
        desc.BufferDesc.RefreshRate.Denominator = denominator;
        desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = FrameCount;
        desc.OutputWindow = _hWnd;
        desc.Windowed = TRUE;
        desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        // �X���b�v�`�F�C���̐���.
        ComPtr<IDXGISwapChain> pSwapChain;
        hr = factory->CreateSwapChain(m_pQueue.Get(), &desc, pSwapChain.GetAddressOf());
        if (FAILED(hr))
        {
            return false;
        }

        // IDXGISwapChain3 ���擾.
        hr = pSwapChain.As(&m_pSwapChain);
        if (FAILED(hr))
        {
            return false;
        }

        // �o�b�N�o�b�t�@�ԍ����擾.
        m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
    }

    // �R�}���h�A���P�[�^�̐���.
    {
        for (auto i = 0u; i < FrameCount; ++i)
        {
            hr = m_pDevice->CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE_DIRECT,
                IID_PPV_ARGS(m_pCmdAllocator[i].GetAddressOf()));
            if (FAILED(hr))
            {
                return false;
            }
        }
    }

    // �R�}���h���X�g�̐���.
    {
        hr = m_pDevice->CreateCommandList(
            0,
            D3D12_COMMAND_LIST_TYPE_DIRECT,
            m_pCmdAllocator[m_FrameIndex].Get(),
            nullptr,
            IID_PPV_ARGS(m_pCmdList.GetAddressOf()));
        if (FAILED(hr))
        {
            return false;
        }
    }

    // �����_�[�^�[�Q�b�g�r���[�̐���.
    {
        // �f�B�X�N���v�^�q�[�v�̐ݒ�.
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.NumDescriptors = FrameCount;
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        desc.NodeMask = 0;

        // �f�B�X�N���v�^�q�[�v�𐶐�.
        hr = m_pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_pHeapRTV.GetAddressOf()));
        if (FAILED(hr))
        {
            return false;
        }

        auto handle = m_pHeapRTV->GetCPUDescriptorHandleForHeapStart();
        auto incrementSize = m_pDevice
            ->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        for (auto i = 0u; i < FrameCount; ++i)
        {
            hr = m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(m_pColorBuffer[i].GetAddressOf()));
            if (FAILED(hr))
            {
                return false;
            }

            D3D12_RENDER_TARGET_VIEW_DESC viewDesc = {};
            viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
            viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
            viewDesc.Texture2D.MipSlice = 0;
            viewDesc.Texture2D.PlaneSlice = 0;

            // �����_�[�^�[�Q�b�g�r���[�̐���.
            m_pDevice->CreateRenderTargetView(m_pColorBuffer[i].Get(), &viewDesc, handle);

            m_HandleRTV[i] = handle;
            handle.ptr += incrementSize;
        }
    }

    // �[�x�X�e���V���o�b�t�@�̐���
    {
        D3D12_HEAP_PROPERTIES prop = {};
        prop.Type = D3D12_HEAP_TYPE_DEFAULT;
        prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        prop.CreationNodeMask = 1;
        prop.VisibleNodeMask = 1;

        D3D12_RESOURCE_DESC resDesc = {};
        resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        resDesc.Alignment = 0;
        resDesc.Width = m_CWindowW;
        resDesc.Height = m_CWindowH;
        resDesc.DepthOrArraySize = 1;
        resDesc.MipLevels = 1;
        resDesc.Format = DXGI_FORMAT_D32_FLOAT;
        resDesc.SampleDesc.Count = 1;
        resDesc.SampleDesc.Quality = 0;
        resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
        resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

        D3D12_CLEAR_VALUE clearValue;
        clearValue.Format = DXGI_FORMAT_D32_FLOAT;
        clearValue.DepthStencil.Depth = 1.0;
        clearValue.DepthStencil.Stencil = 0;

        hr = m_pDevice->CreateCommittedResource(
            &prop,
            D3D12_HEAP_FLAG_NONE,
            &resDesc,
            D3D12_RESOURCE_STATE_DEPTH_WRITE,
            &clearValue,
            IID_PPV_ARGS(m_pDepthBuffer.GetAddressOf()));
        if (FAILED(hr))
        {
            return false;
        }

        // �f�B�X�N���v�^�q�[�v�̐ݒ�.
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
        heapDesc.NumDescriptors = 1;
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        heapDesc.NodeMask = 0;

        hr = m_pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_pHeapDSV.GetAddressOf()));
        if (FAILED(hr))
        {
            return false;
        }

        auto handle = m_pHeapDSV->GetCPUDescriptorHandleForHeapStart();
        auto incrementSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

        D3D12_DEPTH_STENCIL_VIEW_DESC viewDesc = {};
        viewDesc.Format = DXGI_FORMAT_D32_FLOAT;
        viewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        viewDesc.Texture2D.MipSlice = 0;
        viewDesc.Flags = D3D12_DSV_FLAG_NONE;

        m_pDevice->CreateDepthStencilView(m_pDepthBuffer.Get(), &viewDesc, handle);

        m_HandleDSV = handle;
    }

    // �t�F���X�̐���.
    {
        // �t�F���X�J�E���^�[�����Z�b�g.
        for (auto i = 0u; i < FrameCount; ++i)
        {
            m_FenceCounter[i] = 0;
        }

        // �t�F���X�̐���.
        hr = m_pDevice->CreateFence(
            m_FenceCounter[m_FrameIndex],
            D3D12_FENCE_FLAG_NONE,
            IID_PPV_ARGS(m_pFence.GetAddressOf()));
        if (FAILED(hr))
        {
            return false;
        }

        m_FenceCounter[m_FrameIndex]++;

        // �C�x���g�̐���.
        m_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (m_FenceEvent == nullptr)
        {
            return false;
        }
    }

    // �R�}���h���X�g�����.
    m_pCmdList->Close();
}

void Direct3D12::ShutdownD3D12()
{
    assert(m_pQueue != nullptr);
    assert(m_pFence != nullptr);
    assert(m_FenceEvent != nullptr);

    // �V�O�i������.
    m_pQueue->Signal(m_pFence.Get(), m_FenceCounter[m_FrameIndex]);

    // �������ɃC�x���g��ݒ肷��..
    m_pFence->SetEventOnCompletion(m_FenceCounter[m_FrameIndex], m_FenceEvent);

    // �ҋ@����.
    WaitForSingleObjectEx(m_FenceEvent, INFINITE, FALSE);

    // �J�E���^�[�𑝂₷.
    m_FenceCounter[m_FrameIndex]++;

    // �C�x���g�j��.
    if (m_FenceEvent != nullptr)
    {
        CloseHandle(m_FenceEvent);
        m_FenceEvent = nullptr;
    }

    // �t�F���X�j��.
    m_pFence.Reset();

    // �����_�[�^�[�Q�b�g�r���[�̔j��.
    m_pHeapRTV.Reset();
    for (auto i = 0u; i < FrameCount; ++i)
    {
        m_pColorBuffer[i].Reset();
    }

    // �R�}���h���X�g�̔j��.
    m_pCmdList.Reset();

    // �R�}���h�A���P�[�^�̔j��.
    for (auto i = 0u; i < FrameCount; ++i)
    {
        m_pCmdAllocator[i].Reset();
    }

    // �X���b�v�`�F�C���̔j��.
    m_pSwapChain.Reset();

    // �R�}���h�L���[�̔j��.
    m_pQueue.Reset();

    // �f�o�C�X�̔j��.
    m_pDevice.Reset();
}

void Direct3D12::Present(uint32_t vsync)
{
    // ��ʂɕ\��.
    m_pSwapChain->Present(vsync, 0);

    // �V�O�i������.
    const auto currentValue = m_FenceCounter[m_FrameIndex];
    m_pQueue->Signal(m_pFence.Get(), currentValue);

    // �o�b�N�o�b�t�@�ԍ����X�V.
    m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

    // ���̃t���[���̕`�揀�����܂��ł���Αҋ@����
    if (m_pFence->GetCompletedValue() < m_FenceCounter[m_FrameIndex])
    {
        m_pFence->SetEventOnCompletion(m_FenceCounter[m_FrameIndex], m_FenceEvent);
        WaitForSingleObjectEx(m_FenceEvent, INFINITE, FALSE);
    }

    // ���̃t���[���̃t�F���X�J�E���^�[�𑝂₷.
    m_FenceCounter[m_FrameIndex] = currentValue + 1;
}

void Direct3D12::ClearRTV(float R, float G, float B)
{
    // �N���A�J���[�̐ݒ�.
    float clearColor[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    // �����_�[�^�[�Q�b�g�r���[���N���A.
    m_pCmdList->ClearRenderTargetView(m_HandleRTV[m_FrameIndex], clearColor, 0, nullptr);
}

void Direct3D12::ClearDSV()
{
    // �[�x�X�e���V���r���[���N���A.
    m_pCmdList->ClearDepthStencilView(m_HandleDSV, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}


void Direct3D12::StartRecordCommand()
{
    //�R�}���h�A���P�[�^�[�̏�����
    m_pCmdAllocator[m_FrameIndex]->Reset();

    //�R�}���h���X�g�̏�����
    m_pCmdList->Reset(m_pCmdAllocator[m_FrameIndex].Get(), nullptr);

    // ���\�[�X�o���A�̐ݒ�.
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = m_pColorBuffer[m_FrameIndex].Get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    // ���\�[�X�o���A.
    m_pCmdList->ResourceBarrier(1, &barrier);
}

void Direct3D12::EndRecordCommand()
{
    // ���\�[�X�o���A�̐ݒ�.
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = m_pColorBuffer[m_FrameIndex].Get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    // ���\�[�X�o���A.
    m_pCmdList->ResourceBarrier(1, &barrier);

    // �R�}���h�̋L�^���I��.
    m_pCmdList->Close();
}

void Direct3D12::RunCommand()
{
    // �R�}���h�����s.
    ID3D12CommandList* ppCmdLists[] = { m_pCmdList.Get() };
    m_pQueue->ExecuteCommandLists(1, ppCmdLists);
}
