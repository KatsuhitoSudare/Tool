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
				D3D_DRIVER_TYPE_WARP,					// Windows Advanced Rasterizer
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

			return TRUE;
		}
	}
}



