#pragma once
#include<Windows.h>
#include<tchar.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include<vector>

#include<d3dcompiler.h>
#include<DirectXTex.h>
#include<d3dx12.h>
#include<wrl/client.h>

#pragma comment(lib,"DirectXTex.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

using Microsoft::WRL::ComPtr;

class Direct3D12
{
public:
	static void InitD3D12(HWND _hWmd);

private:
	static inline ComPtr<IDXGIFactory4>					_dxgiFactory;
	static inline ComPtr<ID3D12Device6>					_dev;
	static inline ComPtr<ID3D12CommandAllocator>		_cmdAllocator;
	static inline ComPtr<ID3D12GraphicsCommandList>		_cmdList;
	static inline ComPtr<ID3D12CommandQueue>			_cmdQueue;
	static inline ComPtr<IDXGISwapChain4>				_swapchain;


};

