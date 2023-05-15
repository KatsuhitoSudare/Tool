#include "RenderTergetView.h"
#include "Direct3D12.h"

RenderTergetView::RenderTergetView()
:rtvHeap(nullptr)
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[�Ȃ̂œ��RRTV
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = 2;//�\���̂Q��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//���Ɏw��Ȃ�

	auto hr = D3D12->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeap));
	if (SUCCEEDED(hr))
	{
		//�f�B�X�N���v�^�n���h���̐擪
		handle.resize(2);
		handle[0] = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		handle[1].ptr = handle[0].ptr += D3D12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		backBuffer.resize(2);//�o�b�N�o�b�t�@�̃T�C�Y�����킹��
		for (int i = 0; i < backBuffer.size(); i++)
		{
			//�o�b�N�o�b�t�@�̍쐬�ƕR�Â�
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
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[�Ȃ̂œ��RRTV
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = 2;//�\���̂Q��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//���Ɏw��Ȃ�


}

void RenderTergetView::CreateRenderTerget(IDXGISwapChain4* swapchain, int NumBffer)
{

}
