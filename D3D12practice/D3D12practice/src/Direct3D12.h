#pragma once
/*****************************************************************//**
 * \file   Direct3D12.h
 * \brief  
 * 
 * \author 簾勝仁
 * \date   5NAME_JP 2023
 *********************************************************************/
#include<d3d12.h>
#include<dxgi1_6.h>
#include"RenderTergetView.h"

#define COMSAFERELEASE(o){if(o != nullptr){o->Release();};}

/**
 * @class			Direct3D12
 * @brief			Direct3D12を使うためのメインクラス：複数のレンダリングエンジンに対応させるためにstaticじゃなくシングルトンにした
 */
class Direct3D12
{
public:
	/**
	 * @brief          このクラスのインスタンスを取得する関数
	 * @fn             GetInstatnce
	 * @param[in]      
	 * @param[out]     
	 * @return         このクラスのインスタンス
	 * @author         簾勝仁      
	 * @attention      
	 * 
	 */
	static Direct3D12* GetInstatnce();

	/**
	 * @brief          このクラスの終了処理
	 * @fn             Direct3D12ShutDown
	 * @param[in]      
	 * @param[out]     
	 * @return         
	 * @author         簾勝仁      
	 * @attention	   終了時に必ず一度呼び出してください
	 * 
	 */
	void Direct3D12ShutDown();

	/**
	 * @brief          初期化関数
	 * @fn             
	 * @param[in]      
	 * @param[out]     
	 * @return         結果
	 * @author         簾勝仁      
	 * @attention      
	 * 
	 */
	BOOL Direct3D12Initialize();

	/**
	 * @brief          デバイスを受け取る関数
	 * @fn
	 * @param[in]
	 * @param[out]
	 * @return         デバイス
	 * @author         簾勝仁
	 * @attention
	 *
	 */
	ID3D12Device* GetDevice();

	/**
	 * @brief          スワップチェインを受け取る関数
	 * @fn
	 * @param[in]
	 * @param[out]
	 * @return         スワップチェイン
	 * @author         簾勝仁
	 * @attention
	 *
	 */
	IDXGISwapChain4* GetSwapChain();

	/**
	 * @brief          描画開始時に呼び出す
	 * @fn
	 * @param[in]
	 * @param[out]
	 * @return         なし
	 * @author         簾勝仁
	 * @attention	   描画開始時に必ず呼び出す
	 *
	 */
	void RenderingStart();

	/**
	 * @brief          コマンドリストの取得関数
	 * @fn
	 * @param[in]
	 * @param[out]
	 * @return         なし
	 * @author         簾勝仁
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

