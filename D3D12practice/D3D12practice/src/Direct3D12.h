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

	~Direct3D12();
private:
	Direct3D12();
	static inline Direct3D12* s_pInstance;
	ID3D12Device*			  m_pDevice;
	IDXGISwapChain4*		  m_pSwapChain;
	IDXGIFactory6*			  m_pFactory;
	ID3D12CommandAllocator*   m_pAllocator;
	ID3D12CommandList*		  m_pCommandList;
	ID3D12CommandQueue*       m_pQueue;
};

#define D3D12 Direct3D12::GetInstatnce()

