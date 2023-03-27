#include "D3D11RenderingEngin.h"

namespace KALEIDOSCOPE
{
	namespace RENDARINGENGIN
	{
		D3D11RenderingEngin::D3D11RenderingEngin()
		{

		}

		D3D11RenderingEngin::~D3D11RenderingEngin()
		{

		}

		BOOL D3D11RenderingEngin::D3D11RenderingEnginInit()
		{
			//エラー用
			HRESULT hr = S_OK;

			//DeviceのFeatureLivel用
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

			D3D_DRIVER_TYPE driverTypes[] =
			{
				D3D_DRIVER_TYPE_HARDWARE,
				D3D_DRIVER_TYPE_WARP,	
				D3D_DRIVER_TYPE_REFERENCE,
				D3D_DRIVER_TYPE_SOFTWARE,
			};

			unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

			//Deviceの作成
			for (int i = 0; i < numDriverTypes; i++)
			{
				hr = D3D11CreateDevice(NULL, driverTypes[i], NULL, 0, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &m_pDevice, &level, &m_pContext);
				if (SUCCEEDED(hr))
				{
					break;
				}
			}

			//サイズをせってい
			m_RendertergetWidth = 1280;
			m_RenderTergetHeight = 720;
		
			// 1. レンダーターゲットテクスチャの作成
			D3D11_TEXTURE2D_DESC rtTextureDesc;
			ZeroMemory(&rtTextureDesc, sizeof(rtTextureDesc));
			rtTextureDesc.Width = m_RendertergetWidth;
			rtTextureDesc.Height = m_RenderTergetHeight;
			rtTextureDesc.MipLevels = 1;
			rtTextureDesc.ArraySize = 1;
			rtTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			rtTextureDesc.SampleDesc.Count = 1;
			rtTextureDesc.SampleDesc.Quality = 0;
			rtTextureDesc.Usage = D3D11_USAGE_DEFAULT;
			rtTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			rtTextureDesc.CPUAccessFlags = 0;
			rtTextureDesc.MiscFlags = 0;

			hr = m_pDevice->CreateTexture2D(&rtTextureDesc, nullptr, &m_pRenderingTergetTexture);
			if (FAILED(hr))
			{
				return FALSE;
			}

			hr = m_pDevice->CreateRenderTargetView(m_pRenderingTergetTexture,nullptr,&m_rtv);
			if (FAILED(hr))
			{
				return FALSE;
			}

			D3D11_TEXTURE2D_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
			depthStencilDesc.Width = m_RendertergetWidth;
			depthStencilDesc.Height = m_RenderTergetHeight;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.CPUAccessFlags = 0;
			depthStencilDesc.MiscFlags = 0;
			hr = m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &m_DST);
			if (SUCCEEDED(hr)) {
				hr = m_pDevice->CreateDepthStencilView(m_DST, nullptr, &m_DSV);
			}

			m_pContext->OMSetRenderTargets(1,&m_rtv,m_DSV);


			return TRUE;
		}
		void D3D11RenderingEngin::SetRenderTerget()
		{
			m_pContext->OMSetRenderTargets(1, &m_rtv, m_DSV);
			float col[4] = { 0.6f,0.6f,0.6f,1.0f };
			m_pContext->ClearRenderTargetView(m_rtv,col);
		}
		ID3D11Texture2D* D3D11RenderingEngin::GetRenderTexture()
		{
			return m_pRenderingTergetTexture;
		}
	}
}



