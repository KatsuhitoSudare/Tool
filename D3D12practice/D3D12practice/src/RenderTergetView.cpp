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
	if (SUCCEEDED(hr))
	{
		//ディスクリプタハンドルの先頭
		handle.resize(2);
		handle[0] = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		handle[1].ptr = handle[0].ptr += D3D12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		backBuffer.resize(2);//バックバッファのサイズを合わせる
		for (int i = 0; i < backBuffer.size(); i++)
		{
			//バックバッファの作成と紐づけ
			D3D12->GetSwapChain()->GetBuffer(i,IID_PPV_ARGS(&backBuffer[i]));
			D3D12->GetDevice()->CreateRenderTargetView(
				backBuffer[i],
				nullptr,
				handle[i]
				);
		}
	}
}

RenderTergetView::~RenderTergetView()
{
	COMSAFERELEASE(rtvHeap);
	COMSAFERELEASE(backBuffer[0]);
	COMSAFERELEASE(backBuffer[1]);
}

void RenderTergetView::CreateRenderTerget()
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビューなので当然RTV
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = 2;//表裏の２つ
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//特に指定なし


}

void RenderTergetView::CreateRenderTerget(IDXGISwapChain4* swapchain, int NumBffer)
{

}
