#include "RenderTergetView.h"
#include "Direct3D12.h"

RenderTergetView::RenderTergetView()
:rtvHeap(nullptr)
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビューなので当然RTV
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = 2;//表裏の２つ
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//特に指定なし

	auto hr = D3D12->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeap));

}

RenderTergetView::~RenderTergetView()
{
}
