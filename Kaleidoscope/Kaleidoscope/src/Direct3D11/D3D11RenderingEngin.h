#pragma once
#include<Windows.h>
#include<d3d11.h>
#include<dxgi.h>
#include<GLFW/glfw3.h>



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
			static BOOL D3D11RenderingEnginInit();

			static void SetRenderTerget();

			static GLuint GetRenderedImage();

			static void MeshRender();

		private:
			static inline ID3D11Device*				m_pDevice;	/*DirectX11のDevice*/
			static inline ID3D11DeviceContext*		m_pContext;	/*DirectX11のDeviceContext*/
			static inline ID3D11Texture2D*			m_pRenderingTergetTexture;	/*レンダリング先にするテクスチャ*/
			static inline ID3D11RenderTargetView*	m_rtv;
			static inline ID3D11DepthStencilView*	m_DSV;
			static inline ID3D11Texture2D*			m_DST;
			static inline UINT						m_RendertergetWidth,m_RenderTergetHeight;/*レンダーターゲットの幅*/
		};
	}
}




