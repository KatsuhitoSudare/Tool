#pragma once
/*****************************************************************//**
 * \file   Direct3D12.h
 * \brief  
 * 
 * \author �����m
 * \date   5NAME_JP 2023
 *********************************************************************/
#include<d3d12.h>
#include<dxgi1_6.h>
#include"RenderTergetView.h"

#define COMSAFERELEASE(o){if(o != nullptr){o->Release();};}

/**
 * @class			Direct3D12
 * @brief			Direct3D12���g�����߂̃��C���N���X�F�����̃����_�����O�G���W���ɑΉ������邽�߂�static����Ȃ��V���O���g���ɂ���
 */
class Direct3D12
{
public:
	/**
	 * @brief          ���̃N���X�̃C���X�^���X���擾����֐�
	 * @fn             GetInstatnce
	 * @param[in]      
	 * @param[out]     
	 * @return         ���̃N���X�̃C���X�^���X
	 * @author         �����m      
	 * @attention      
	 * 
	 */
	static Direct3D12* GetInstatnce();

	/**
	 * @brief          ���̃N���X�̏I������
	 * @fn             Direct3D12ShutDown
	 * @param[in]      
	 * @param[out]     
	 * @return         
	 * @author         �����m      
	 * @attention	   �I�����ɕK����x�Ăяo���Ă�������
	 * 
	 */
	void Direct3D12ShutDown();

	/**
	 * @brief          �������֐�
	 * @fn             
	 * @param[in]      
	 * @param[out]     
	 * @return         ����
	 * @author         �����m      
	 * @attention      
	 * 
	 */
	BOOL Direct3D12Initialize();

	/**
	 * @brief          �f�o�C�X���󂯎��֐�
	 * @fn
	 * @param[in]
	 * @param[out]
	 * @return         �f�o�C�X
	 * @author         �����m
	 * @attention
	 *
	 */
	ID3D12Device* GetDevice();

	/**
	 * @brief          �X���b�v�`�F�C�����󂯎��֐�
	 * @fn
	 * @param[in]
	 * @param[out]
	 * @return         �X���b�v�`�F�C��
	 * @author         �����m
	 * @attention
	 *
	 */
	IDXGISwapChain4* GetSwapChain();

	/**
	 * @brief          �`��J�n���ɌĂяo��
	 * @fn
	 * @param[in]
	 * @param[out]
	 * @return         �Ȃ�
	 * @author         �����m
	 * @attention	   �`��J�n���ɕK���Ăяo��
	 *
	 */
	void RenderingStart();

	/**
	 * @brief          �R�}���h���X�g�̎擾�֐�
	 * @fn
	 * @param[in]
	 * @param[out]
	 * @return         �Ȃ�
	 * @author         �����m
	 * @attention	   
	 *
	 */
	ID3D12GraphicsCommandList* GetCommandlist();

	~Direct3D12();
private:
	Direct3D12();
	static inline Direct3D12*			s_pInstance;
	ID3D12Device*						m_pDevice;
	IDXGISwapChain4*					m_pSwapChain;
	IDXGIFactory4*						m_pFactory;
	ID3D12CommandAllocator*				m_pAllocator;
	ID3D12GraphicsCommandList*			m_pCommandList;
	ID3D12CommandQueue*					m_pQueue;
	ID3D12Fence*						m_pFence;
	RenderTergetView*					m_pRtv;
	UINT								m_FenceVal;
};

#define D3D12 Direct3D12::GetInstatnce()

