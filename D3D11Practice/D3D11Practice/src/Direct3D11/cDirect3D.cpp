#include"cDirect3D.h"
#include"..\cWindowManager.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

BOOL cDirect3D::Direct3DInit()	
{
	HWND hWnd = cWindowManager::GetWindowHandole();

	HRESULT  hr = 0;
	UINT         numModes = 0;
	DXGI_MODE_DESC* DisplayMode = nullptr;
	unsigned int numerator = 60;			// ���q
	unsigned int denominator = 1;			// ����

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,					// Windows Advanced Rasterizer
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
	};

	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL   level{};
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,					// DirectX11.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_11_0,					// DirectX11�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_1,					// DirectX10.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_0,					// DirectX10�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_3,					// DirectX9.3�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_2,					// DirectX9.2�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_1					// Direct9.1�Ή�GPU���x��
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	RECT                rect;

	GetClientRect(hWnd, &rect);
	m_CWindowW = (UINT)(rect.right - rect.left);
	m_CWindowH = (UINT)(rect.bottom - rect.top);

	//�t�@�N�g�����쐬
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (LPVOID*)&m_pDxgiFactory);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�t�@�N�g���̎擾�Ɏ��s", "����", MB_ICONINFORMATION);
		return FALSE;
	}

	//���ڂ���Ă���r�f�I�J�[�h�̎擾
	hr = m_pDxgiFactory->EnumAdapters(0,m_pDxgiAdapter.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�A�_�v�^�̎擾�Ɏ��s", "����", MB_ICONINFORMATION);
		return FALSE;
	}

	//���j�^�[�̏��擾
	hr = m_pDxgiAdapter->EnumOutputs(0, m_pDxgiOutput.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(hWnd, "���j�^�[�̏��擾�Ɏ��s", "����", MB_ICONINFORMATION);
		return FALSE;
	}

	hr = m_pDxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "���j�^�[�̏��擾�Ɏ��s", "����", MB_ICONINFORMATION);
		return FALSE;
	}

	DisplayMode = new DXGI_MODE_DESC[numModes];
	if (!DisplayMode) {
		MessageBox(hWnd, "���j�^�[�̏��擾�Ɏ��s", "����", MB_ICONINFORMATION);
		return FALSE;
	}

	hr = m_pDxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, DisplayMode);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "���j�^�[�̏��擾�Ɏ��s", "����", MB_ICONINFORMATION);
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

	for (UINT TypeNum = 0; TypeNum < numDriverTypes; TypeNum++)
	{
		hr = D3D11CreateDevice(NULL,
			driverTypes[TypeNum],
			NULL,
			0,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&m_pD3DDevice,
			&level,
			&m_pD3DContext);
		if (SUCCEEDED(hr))
		{
			break;
		}
	}
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�f�o�C�X�̍쐬�Ɏ��s", "����", MB_ICONINFORMATION);
		delete[] DisplayMode;
		return FALSE;
	}



	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));									// �[���N���A
	sd.BufferCount = 1;												// �o�b�N�o�b�t�@�̐�
	sd.BufferDesc.Width = m_CWindowW;								// �o�b�N�o�b�t�@�̕�
	sd.BufferDesc.Height = m_CWindowH;								// �o�b�N�o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				// �o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B �͈͂O�D�O����P�D�O)
	sd.BufferDesc.RefreshRate.Numerator = numerator;				// ���t���b�V�����[�g�i����j
	sd.BufferDesc.RefreshRate.Denominator = denominator;			// ���t���b�V�����[�g�i���q�j
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;				// �o�b�N�o�b�t�@�̎g�p���@
	sd.OutputWindow = hWnd;											// �֘A�t����E�C���h�E
	sd.SampleDesc.Count = 1;										// �}���`�T���v���̐�
	sd.SampleDesc.Quality = 0;										// �}���`�T���v���̃N�I���e�B
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;				// ���[�h�̎����؂�ւ�


	hr = m_pDxgiFactory->CreateSwapChain(m_pD3DDevice.Get(), &sd, m_pSwapChain.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�X���b�v�`�F�C���̍쐬�Ɏ��s", "����", MB_ICONINFORMATION);
		delete[] DisplayMode;
		return FALSE;
	}

	delete[] DisplayMode;

	//�o�b�N�o�b�t�@�̎擾
	hr = m_pSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�o�b�N�o�b�t�@�̎擾�Ɏ��s", "����", MB_ICONINFORMATION);
		return FALSE;
	}

	m_rtv.CreateRenderTerget(m_pBackBuffer.Get(),1920,1080);
	m_rtv.SetRenderTerget(true);

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)m_CWindowW;
	viewport.Height = (FLOAT)m_CWindowH;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_pD3DContext->RSSetViewports(1, &viewport);

	return TRUE;
}

void cDirect3D::ClearRenderTarget(float R, float G, float B)
{
	m_rtv.ClearRenderTarget(R, G, B);
}

void cDirect3D::SwapBuffuer()
{
	m_pSwapChain->Present(1,0);
}

ID3D11Device* cDirect3D::GetDevice()
{
	return m_pD3DDevice.Get();
}

ID3D11DeviceContext* cDirect3D::GetContext()
{
	return m_pD3DContext.Get();
}

void cDirect3D::SwapChainResizeBuffer(UINT w,UINT h)
{	
	if (m_pSwapChain != nullptr)
	{
		m_rtv.CleanupRenderTarget();
		m_pSwapChain->ResizeBuffers(0, w, h, DXGI_FORMAT_UNKNOWN, 0);
		m_pBackBuffer.Reset();
		auto hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
		m_rtv.CreateRenderTerget(m_pBackBuffer.Get(),w,h);
	}
}


