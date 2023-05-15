#pragma once
#include<d3d12.h>
#include<vector>

class RenderTergetView
{
public:
	RenderTergetView();
	~RenderTergetView();

	void CreateRenderTerget();
	void CreateRenderTerget(IDXGISwapChain4* swapchain,int NumBffer);
	

private:
	ID3D12DescriptorHeap*						rtvHeap;   //�����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v
	std::vector<ID3D12Resource*>				backBuffer;//DirectX11�̃o�b�N�o�b�t�@�̃e�N�X�`���I�ȓz
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>	handle;    //�f�B�X�N���v�^�q�[�v�̊J�n�ʒu
};

