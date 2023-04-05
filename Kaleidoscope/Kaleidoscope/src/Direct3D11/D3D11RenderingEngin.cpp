#include "D3D11RenderingEngin.h"
#include"GLFW/glfw3native.h"
#include<gl/GL.h>
#include<gl/GLU.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

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

			D3D11_TEXTURE2D_DESC desc;
			m_pRenderingTergetTexture->GetDesc(&desc);
			UINT width = desc.Width;
			UINT height = desc.Height;
			UINT rowPitch = desc.Width * 4; // RGBAフォーマットを想定して4バイトずつ
			slicePitch   = rowPitch * desc.Height;
			textureData = new BYTE[slicePitch];

			// ステージングテクスチャを作成する
			desc.Usage = D3D11_USAGE_STAGING;
			desc.BindFlags = 0;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			desc.MiscFlags = 0;
			hr = m_pDevice->CreateTexture2D(&desc, NULL, &stagingTexture);

			// OpenGLのテクスチャオブジェクトを作成する
			glBindTexture(GL_TEXTURE_2D, glTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

			// テクスチャフィルタリングを設定する
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// テクスチャのラップモードを設定する
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			return TRUE;
		}

		void D3D11RenderingEngin::D3D11RenderingEnginShutDown()
		{
			// メモリを解放する
			delete[] textureData;
			stagingTexture->Release();
			m_pDevice->Release();
			m_pContext->Release();
			m_pRenderingTergetTexture->Release();
			m_DST->Release();
			m_DSV->Release();
			m_rtv->Release();
		}

		void D3D11RenderingEngin::SetRenderTerget()
		{
			m_pContext->OMSetRenderTargets(1, &m_rtv, m_DSV);
			float col[4] = { 0.6f,0.6f,0.6f,1.0f };
			m_pContext->ClearRenderTargetView(m_rtv,col);
		}

		GLuint D3D11RenderingEngin::GetRenderedImage()
		{
			//データをコピーする
			m_pContext->CopyResource(stagingTexture, m_pRenderingTergetTexture);
			// ステージングテクスチャのデータをバッファにコピーする
			D3D11_MAPPED_SUBRESOURCE mapped;
			m_pContext->Map(stagingTexture, 0, D3D11_MAP_READ, 0, &mapped);
			memcpy(textureData, mapped.pData, slicePitch);
			m_pContext->Unmap(stagingTexture, 0);
			return glTexture;
		}
	}
}



