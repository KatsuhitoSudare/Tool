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
			//�G���[�p
			HRESULT hr = S_OK;

			//Device��FeatureLivel�p
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

			D3D_DRIVER_TYPE driverTypes[] =
			{
				D3D_DRIVER_TYPE_HARDWARE,
				D3D_DRIVER_TYPE_WARP,					// Windows Advanced Rasterizer
				D3D_DRIVER_TYPE_REFERENCE,
				D3D_DRIVER_TYPE_SOFTWARE,
			};

			unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

			//Device�̍쐬
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



