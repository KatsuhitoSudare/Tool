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
	static inline ID3D12DescriptorHeap*			rtvHeap;	   //�����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v
	std::vector<ID3D12Resource*>				backBuffer;	   //DirectX11�̃o�b�N�o�b�t�@�̃e�N�X�`���I�ȓz
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>	handle;		   //�f�B�X�N���v�^�q�[�v�̊J�n�ʒu
	static inline int							TotalNumBuffer;//�����_�[�^�[�Q�b�g�S�̂̐�
	const UINT									RTVIncrementSize;
};

