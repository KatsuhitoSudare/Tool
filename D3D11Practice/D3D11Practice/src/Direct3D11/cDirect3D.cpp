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
	unsigned int numerator = 60;			// 分子
	unsigned int denominator = 1;			// 分母

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
		D3D_FEATURE_LEVEL_11_1,					// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,					// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,					// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,					// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,					// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,					// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1					// Direct9.1対応GPUレベル
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	RECT                rect;

	GetClientRect(hWnd, &rect);
	m_CWindowW = (UINT)(rect.right - rect.left);
	m_CWindowH = (UINT)(rect.bottom - rect.top);

	//ファクトリを作成
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (LPVOID*)&m_pDxgiFactory);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "ファクトリの取得に失敗", "結果", MB_ICONINFORMATION);
		return FALSE;
	}

	//搭載されているビデオカードの取得
	hr = m_pDxgiFactory->EnumAdapters(0,m_pDxgiAdapter.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(hWnd, "アダプタの取得に失敗", "結果", MB_ICONINFORMATION);
		return FALSE;
	}

	//モニターの情報取得
	hr = m_pDxgiAdapter->EnumOutputs(0, m_pDxgiOutput.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(hWnd, "モニターの情報取得に失敗", "結果", MB_ICONINFORMATION);
		return FALSE;
	}

	hr = m_pDxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "モニターの情報取得に失敗", "結果", MB_ICONINFORMATION);
		return FALSE;
	}

	DisplayMode = new DXGI_MODE_DESC[numModes];
	if (!DisplayMode) {
		MessageBox(hWnd, "モニターの情報取得に失敗", "結果", MB_ICONINFORMATION);
		return FALSE;
	}

	hr = m_pDxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, DisplayMode);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "モニターの情報取得に失敗", "結果", MB_ICONINFORMATION);
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
		MessageBox(hWnd, "デバイスの作成に失敗", "結果", MB_ICONINFORMATION);
		delete[] DisplayMode;
		return FALSE;
	}



	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));									// ゼロクリア
	sd.BufferCount = 1;												// バックバッファの数
	sd.BufferDesc.Width = m_CWindowW;								// バックバッファの幅
	sd.BufferDesc.Height = m_CWindowH;								// バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				// バックバッファフォーマット(R,G,B 範囲０．０から１．０)
	sd.BufferDesc.RefreshRate.Numerator = numerator;				// リフレッシュレート（分母）
	sd.BufferDesc.RefreshRate.Denominator = denominator;			// リフレッシュレート（分子）
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;				// バックバッファの使用方法
	sd.OutputWindow = hWnd;											// 関連付けるウインドウ
	sd.SampleDesc.Count = 1;										// マルチサンプルの数
	sd.SampleDesc.Quality = 0;										// マルチサンプルのクオリティ
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;				// モードの自動切り替え


	hr = m_pDxgiFactory->CreateSwapChain(m_pD3DDevice.Get(), &sd, m_pSwapChain.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBox(hWnd, "スワップチェインの作成に失敗", "結果", MB_ICONINFORMATION);
		delete[] DisplayMode;
		return FALSE;
	}

	delete[] DisplayMode;

	//バックバッファの取得
	hr = m_pSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "バックバッファの取得に失敗", "結果", MB_ICONINFORMATION);
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


