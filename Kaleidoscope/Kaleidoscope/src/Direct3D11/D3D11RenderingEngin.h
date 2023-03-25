#pragma once
#include<Windows.h>
#include<d3d11.h>
#include<dxgi.h>
#include"RenderTergetView.h"

//=================================================
// D3D11のレンダリングの機能のみを持ったクラス
//=================================================
namespace KALEIDOSCOPE
{
	namespace RENDARINGENGIN
	{
		class D3D11RenderingEngin
		{
		public:
			//コンストラクタ
			D3D11RenderingEngin();
			//デストラクタ
			~D3D11RenderingEngin();
			//初期化関数
			BOOL D3D11RenderingEnginInit();

		private:
			ID3D11Device*		 m_pDevice;/*DirectX11のDevice*/
			ID3D11DeviceContext* m_pContext;/*DirectX11のDeviceContext*/
			IDXGIFactory*		 m_pFactory;
		};
	}
}




