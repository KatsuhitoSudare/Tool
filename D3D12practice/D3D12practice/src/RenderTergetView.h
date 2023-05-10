#pragma once
#include<d3d12.h>
#include<vector>

class RenderTergetView
{
public:
	RenderTergetView();
	~RenderTergetView();
private:
	ID3D12DescriptorHeap*        rtvHeap;   //レンダーターゲット用のディスクリプタヒープ
	std::vector<ID3D12Resource*> backBuffer;//DirectX11のバックバッファのテクスチャ的な奴
	D3D12_CPU_DESCRIPTOR_HANDLE  handle;    //ディスクリプタヒープの開始位置

};

