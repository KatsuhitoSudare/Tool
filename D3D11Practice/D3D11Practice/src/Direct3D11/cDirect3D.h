#pragma once

#include<Windows.h>
#include<dxgi1_2.h>
#include<d3d11.h>
#include<wrl/client.h>
#include"RenderTergetView.h"

using Microsoft::WRL::ComPtr;

class cDirect3D
{
public:
	static BOOL Direct3DInit();
	static void ClearRenderTarget(float R,float G,float B);
	static void SwapBuffuer();
	static ID3D11Device* GetDevice();
	static ID3D11DeviceContext* GetContext();
	static void SwapChainResizeBuffer(UINT, UINT);

private:
	static inline UINT                           m_CWindowW;
	static inline UINT                           m_CWindowH;
	
	static inline ComPtr<ID3D11Device>           m_pD3DDevice;
	static inline ComPtr<ID3D11DeviceContext>    m_pD3DContext;
	static inline ComPtr<IDXGISwapChain>         m_pSwapChain;
	static inline ComPtr<IDXGIAdapter>           m_pDxgiAdapter;
	static inline ComPtr<IDXGIDevice>            m_pDxgiDevice;
	static inline ComPtr<IDXGIFactory>           m_pDxgiFactory;
	static inline ComPtr<IDXGIOutput>            m_pDxgiOutput;
	static inline RenderTergetView				 m_rtv;
	static inline ComPtr<ID3D11Texture2D>                      m_pBackBuffer;
};

