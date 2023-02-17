#pragma once
#include<Windows.h>
#include<tchar.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include<vector>

#include<d3dcompiler.h>
#include<wrl/client.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

using Microsoft::WRL::ComPtr;

class Direct3D12
{
public:
    //�������֐�
	static BOOL InitD3D12(HWND _hWmd);

    //�o�b�t�@����������
    static void Present(uint32_t vsync);

    //�����_�[�^�[�Q�b�g�̃N���A
    static void CreaterRTV(float R,float G,float B);

    //�[�x�X�e���V���r���[�ƃo�b�t�@�̃N���A
    static void CreaterDSV();

    //�R�}���h�̋L�^���J�n����֐�:�`��̏����̑O�ɍs��
    static void StartRecordCommand();



private:
    static const uint32_t FrameCount = 2;   // �t���[���o�b�t�@���ł�.

    static inline ComPtr<ID3D12Device>                   m_pDevice;                      // �f�o�C�X�ł�.
    static inline ComPtr<ID3D12CommandQueue>             m_pQueue;                       // �R�}���h�L���[�ł�.
    static inline ComPtr<IDXGISwapChain3>                m_pSwapChain;                   // �X���b�v�`�F�C���ł�.
    static inline ComPtr<ID3D12Resource>                 m_pColorBuffer[FrameCount];     // �J���[�o�b�t�@�ł�.
    static inline ComPtr<ID3D12Resource>                 m_pDepthBuffer;                 // �[�x�X�e���V���o�b�t�@�ł�.
    static inline ComPtr<ID3D12CommandAllocator>         m_pCmdAllocator[FrameCount];    // �R�}���h�A���P�[�^�ł�.
    static inline ComPtr<ID3D12GraphicsCommandList>      m_pCmdList;                     // �R�}���h���X�g�ł�.
    static inline ComPtr<ID3D12DescriptorHeap>           m_pHeapRTV;                     // �f�B�X�N���v�^�q�[�v�ł�(�����_�[�^�[�Q�b�g�r���[).
    static inline ComPtr<ID3D12DescriptorHeap>           m_pHeapDSV;
    static inline ComPtr<ID3D12Fence>                    m_pFence;                       // �t�F���X�ł�.
    static inline ComPtr<ID3D12DescriptorHeap>           m_pHeapCBV_SRV_UAV;             // ���ύX:�f�B�X�N���v�^�q�[�v�ł�(�萔�o�b�t�@�r���[�E�V�F�[�_���\�[�X�r���[�E�A���I�[�_�[�h�A�N�Z�X�r���[)
    static inline ComPtr<ID3D12Resource>                 m_pVB;                          // ���_�o�b�t�@�ł�.
    static inline ComPtr<ID3D12Resource>                 m_pIB;                          // �C���f�b�N�X�o�b�t�@�ł�.
    static inline ComPtr<ID3D12Resource>                 m_pCB[FrameCount * 2];          // �萔�o�b�t�@�ł�.
    static inline ComPtr<ID3D12RootSignature>            m_pRootSignature;               // ���[�g�V�O�j�`���ł�.
    static inline ComPtr<ID3D12PipelineState>            m_pPSO;                         // �p�C�v���C���X�e�[�g�ł�.
    static inline HANDLE                                 m_FenceEvent;                   // �t�F���X�C�x���g�ł�.
    static inline uint64_t                               m_FenceCounter[FrameCount];     // �t�F���X�J�E���^�[�ł�.
    static inline uint32_t                               m_FrameIndex;                   // �t���[���ԍ��ł�.
    static inline D3D12_CPU_DESCRIPTOR_HANDLE            m_HandleDSV;                    // CPU�f�B�X�N���v�^(�[�x�X�e���V���r���[)�ł�.   
    static inline D3D12_CPU_DESCRIPTOR_HANDLE            m_HandleRTV[FrameCount];        // CPU�f�B�X�N���v�^(�����_�[�^�[�Q�b�g�r���[)�ł�.
    static inline D3D12_VERTEX_BUFFER_VIEW               m_VBV;                          // ���_�o�b�t�@�r���[�ł�.
    static inline D3D12_INDEX_BUFFER_VIEW                m_IBV;                          // �C���f�b�N�X�o�b�t�@�r���[�ł�.
    static inline D3D12_VIEWPORT                         m_Viewport;                     // �r���[�|�[�g�ł�.
    static inline D3D12_RECT                             m_Scissor;                      // �V�U�[��`�ł�.

};

