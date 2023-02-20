﻿//-----------------------------------------------------------------------------
// File : ConstantBuffer.h
// Desc : Constant Buffer Module. 
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <d3d12.h>
#include <ComPtr.h>
#include <vector>


//-----------------------------------------------------------------------------
// Forward Declarations.
//-----------------------------------------------------------------------------
class DescriptorHandle;
class DescriptorPool;


///////////////////////////////////////////////////////////////////////////////
// ConstantBuffer class
///////////////////////////////////////////////////////////////////////////////
class ConstantBuffer
{
    //=========================================================================
    // list of friend classes and methods.
    //=========================================================================
    /* NOTHING */

public:
    //=========================================================================
    // public variables.
    //=========================================================================
    /* NOTHING */

    //=========================================================================
    // public methods.
    //=========================================================================

    //-------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //-------------------------------------------------------------------------
    ConstantBuffer();

    //-------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //-------------------------------------------------------------------------
    ~ConstantBuffer();

    //-------------------------------------------------------------------------
    //! @brief      初期化処理を行います.
    //!
    //! @param[in]      pDevice     デバイスです.
    //! @param[in]      pPool       ディスクリプタプールです.
    //! @retval true    初期化に成功.
    //! @retval false   初期化に失敗.
    //-------------------------------------------------------------------------
    bool Init(
        ID3D12Device*   pDevice,
        DescriptorPool* pPool,
        size_t          size);

    //-------------------------------------------------------------------------
    //! @brief      終了処理を行います.
    //-------------------------------------------------------------------------
    void Term();

    //-------------------------------------------------------------------------
    //! @brief      GPU仮想アドレスを取得します.
    //!
    //! @return     GPU仮想アドレスを返却します.
    //-------------------------------------------------------------------------
    D3D12_GPU_VIRTUAL_ADDRESS GetAddress() const;

    //-------------------------------------------------------------------------
    //! @brief      CPUディスクリプタハンドルを取得します.
    //!
    //! @return     CPUディスクリプタハンドルを返却します.
    //-------------------------------------------------------------------------
    D3D12_CPU_DESCRIPTOR_HANDLE GetHandleCPU() const;

    //-------------------------------------------------------------------------
    //! @brief      GPUディスクリプタハンドルを取得します.
    //!
    //! @return     GPUディスクリプタハンドルを返却します.
    //-------------------------------------------------------------------------
    D3D12_GPU_DESCRIPTOR_HANDLE GetHandleGPU() const;

    //-------------------------------------------------------------------------
    //! @brief      メモリマッピング済みポインタを取得します.
    //!
    //! @return     メモリマッピング済みポインタを返却します.
    //-------------------------------------------------------------------------
    void* GetPtr() const;

    //-------------------------------------------------------------------------
    //! @brief      メモリマッピング済みポインタを取得します.
    //!
    //! @return     メモリマッピング済みポインタを返却します.
    //-------------------------------------------------------------------------
    template<typename T>
    T* GetPtr()
    { return reinterpret_cast<T*>(GetPtr()); }

private:
    //=========================================================================
    // private variables.
    //=========================================================================
    ComPtr<ID3D12Resource>          m_pCB;          //!< 定数バッファ.
    DescriptorHandle*               m_pHandle;      //!< ディスクリプタハンドルです.
    DescriptorPool*                 m_pPool;        //!< ディスクリプタプールです.
    D3D12_CONSTANT_BUFFER_VIEW_DESC m_Desc;         //!< 定数バッファビューの構成設定.
    void*                           m_pMappedPtr;   //!< マップ済みポインタ.

    //=========================================================================
    // private methods.
    //=========================================================================
    ConstantBuffer  (const ConstantBuffer&) = delete;       // アクセス禁止.
    void operator = (const ConstantBuffer&) = delete;       // アクセス禁止.
};

