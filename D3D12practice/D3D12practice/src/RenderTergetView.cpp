#include "RenderTergetView.h"
#include "Direct3D12.h"

RenderTergetView::RenderTergetView()
:RTVIncrementSize(D3D12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV))
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[�Ȃ̂œ��RRTV
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT;//�����_�[�^�[�Q�b�g�̍ő吔���쐬
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//���Ɏw��Ȃ�

	auto hr = D3D12->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeap));
}

RenderTergetView::~RenderTergetView()
{
	COMSAFERELEASE(rtvHeap);
	for (int i = 0; i < backBuffer.size(); i++)
	{
		COMSAFERELEASE(backBuffer[i]);
	}
}

bool RenderTergetView::CreateRenderTerget(IDXGISwapChain4* swapchain, int NumBffer)
{
	for (int i = 0; i < NumBffer; i++)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE _handl{};
		_handl.ptr = rtvHeap->GetCPUDescriptorHandleForHeapStart().ptr + RTVIncrementSize * TotalNumBuffer;

		ID3D12Resource* _backbuffer;
		//�o�b�N�o�b�t�@�̍쐬�ƕR�Â�
		swapchain->GetBuffer(i, IID_PPV_ARGS(&_backbuffer));
		D3D12->GetDevice()->CreateRenderTargetView(
			_backbuffer,
			nullptr,
			_handl
		);
		backBuffer.emplace_back(_backbuffer);
		handle.emplace_back(_handl);
	}

	return true;
}

void RenderTergetView::SetRenderTerget(ID3D12GraphicsCommandList* commandlist, int rtvnum, float* CrearColor)
{
	commandlist->OMSetRenderTargets(1,&handle[rtvnum],true,nullptr);
	commandlist->ClearRenderTargetView(handle[rtvnum], CrearColor, 0, nullptr);
}

ID3D12Resource* RenderTergetView::GetRTVResource(int resourcenum)
{
	return backBuffer[resourcenum];
}




