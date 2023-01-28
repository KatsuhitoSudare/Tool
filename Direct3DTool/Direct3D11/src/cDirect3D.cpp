#include "cDirect3D.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

BOOL cDirect3D::Direct3DInit(HWND hWnd)
{
	m_hWnd = hWnd;

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
		MessageBox(hWnd, L"�t�@�N�g���̎擾�Ɏ��s", L"����", MB_ICONINFORMATION);
		return FALSE;
	}

	//���ڂ���Ă���r�f�I�J�[�h�̎擾
	hr = m_pDxgiFactory->EnumAdapters(0,m_pDxgiAdapter.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"�A�_�v�^�̎擾�Ɏ��s", L"����", MB_ICONINFORMATION);
		return FALSE;
	}

	//���j�^�[�̏��擾
	hr = m_pDxgiAdapter->EnumOutputs(0, m_pDxgiOutput.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"���j�^�[�̏��擾�Ɏ��s", L"����", MB_ICONINFORMATION);
		return FALSE;
	}

	hr = m_pDxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"���j�^�[�̏��擾�Ɏ��s", L"����", MB_ICONINFORMATION);
		return FALSE;
	}

	DisplayMode = new DXGI_MODE_DESC[numModes];
	if (!DisplayMode) {
		MessageBox(hWnd, L"���j�^�[�̏��擾�Ɏ��s", L"����", MB_ICONINFORMATION);
		return FALSE;
	}

	hr = m_pDxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, DisplayMode);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"���j�^�[�̏��擾�Ɏ��s", L"����", MB_ICONINFORMATION);
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
		MessageBox(hWnd, L"�f�o�C�X�̍쐬�Ɏ��s", L"����", MB_ICONINFORMATION);
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
		MessageBox(hWnd, L"�X���b�v�`�F�C���̍쐬�Ɏ��s", L"����", MB_ICONINFORMATION);
		delete[] DisplayMode;
		return FALSE;
	}

	delete[] DisplayMode;

	//�o�b�N�o�b�t�@�̎擾
	ComPtr<ID3D11Texture2D> m_pBackBuffer;

	hr = m_pSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"�o�b�N�o�b�t�@�̎擾�Ɏ��s", L"����", MB_ICONINFORMATION);
		return FALSE;
	}
	hr = m_pD3DDevice->CreateRenderTargetView(m_pBackBuffer.Get(), NULL, &m_pRTV);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"�o�b�N�o�b�t�@�̍쐬�Ɏ��s", L"����", MB_ICONINFORMATION);
		return FALSE;
	}

	//�[�x�X�e���V���o�b�t�@�쐬
	D3D11_TEXTURE2D_DESC txDesc;

	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = m_CWindowW;
	txDesc.Height = m_CWindowH;
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = 0;
	txDesc.MiscFlags = 0;

	hr = m_pD3DDevice->CreateTexture2D(&txDesc, NULL, &m_pDepthStencilTexture);

	if (SUCCEEDED(hr)) {
		D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(dsDesc));
		dsDesc.Format = txDesc.Format;
		dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsDesc.Texture2D.MipSlice = 0;
		hr = m_pD3DDevice->CreateDepthStencilView(m_pDepthStencilTexture.Get(), &dsDesc, &m_pDepthStencilView);
	}

	if (FAILED(hr))
	{
		MessageBox(hWnd, L"�[�x�X�e���V���o�b�t�@�̍쐬�Ɏ��s", L"����", MB_ICONINFORMATION);
		return FALSE;
	}

	// �����_�����O�^�[�Q�b�g��ݒ�@�i���j����2D�Ȃ̂�Z�o�b�t�@�����ɂ��Ă���
	m_pD3DContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDepthStencilView.Get());


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
	float clearColor[4] = { R, G, B, 1.0f }; //red,green,blue,alpha

	m_pD3DContext->ClearRenderTargetView(m_pRTV.Get(), clearColor);

	// Z�o�b�t�@�A�X�e���V���o�b�t�@�N���A
	m_pD3DContext->ClearDepthStencilView(
		m_pDepthStencilView.Get(),			// �f�v�X�X�e���V���r���[
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,			// �y�o�b�t�@��1.0�ŃN���A����(0.0f�`1.0f)
		0);				// �X�e���V���o�b�t�@��0�ŃN���A����


}

void cDirect3D::SwapBuffuer()
{
	m_pSwapChain->Present(1,0);
}
