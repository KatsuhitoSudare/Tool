#pragma once
#ifdef _DEBUG
#pragma comment(lib,"Direct3D11_debug.lib")
#else
#pragma comment(lib,"Direct3D11.lib")
#endif // _DEBUG

#include<Windows.h>
#include<dxgi1_2.h>
#include<d3d11.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;


class cDirect3D
{
public:
	static BOOL Direct3DInit(HWND hWnd);
	static void ClearRenderTarget(float R,float G,float B);
	static void SwapBuffuer();
	static ID3D11Device* GetDevice();
	static ID3D11DeviceContext* GetContext();

private:
	static inline UINT                           m_CWindowW;
	static inline UINT                           m_CWindowH;
	static inline HWND                           m_hWnd;
	
	static inline ComPtr<ID3D11Device>           m_pD3DDevice;
	static inline ComPtr<ID3D11DeviceContext>    m_pD3DContext;
	static inline ComPtr<IDXGISwapChain>         m_pSwapChain;
	static inline ComPtr<ID3D11RenderTargetView> m_pRTV;
	static inline ComPtr<IDXGIAdapter>           m_pDxgiAdapter;
	static inline ComPtr<IDXGIDevice>            m_pDxgiDevice;
	static inline ComPtr<IDXGIFactory>           m_pDxgiFactory;
	static inline ComPtr<IDXGIOutput>            m_pDxgiOutput;
	static inline ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	static inline ComPtr<ID3D11Texture2D>        m_pDepthStencilTexture;
};

