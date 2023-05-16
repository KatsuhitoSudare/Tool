#pragma once
#include<d3d12.h>
#include<vector>
#include<dxgi1_6.h>

class RenderTergetView
{
public:
	RenderTergetView();
	~RenderTergetView();
	bool CreateRenderTerget(IDXGISwapChain4* swapchain,int NumBffer);
	void SetRenderTerget(ID3D12GraphicsCommandList* commandlistint,int rtvnum, float* CrearColor);
	ID3D12Resource* GetRTVResource(int resourcenum);

private:
	static inline ID3D12DescriptorHeap*			rtvHeap;	   //レンダーターゲット用のディスクリプタヒープ
	std::vector<ID3D12Resource*>				backBuffer;	   //DirectX11のバックバッファのテクスチャ的な奴
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>	handle;		   //ディスクリプタヒープの開始位置
	static inline int							TotalNumBuffer;//レンダーターゲット全体の数
	const UINT									RTVIncrementSize;
};

