//-----------------------------------------------------------------------------
// File : IESProfile.h
// Desc : IES Profile.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <d3d12.h>
#include <wrl/client.h>
#include <DescriptorPool.h>
#include <ResourceUploadBatch.h>


///////////////////////////////////////////////////////////////////////////////
// IESProfile class
///////////////////////////////////////////////////////////////////////////////
class IESProfile
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
    IESProfile();

    //-------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //-------------------------------------------------------------------------
    ~IESProfile();

    //-------------------------------------------------------------------------
    //! @brief      初期化処理を行います.
    //-------------------------------------------------------------------------
    bool Init(
        ID3D12Device*                   pDevice,
        DescriptorPool*                 pPool,
        const char*                     filePath,
        DirectX::ResourceUploadBatch&   batch);

    //-------------------------------------------------------------------------
    //! @brief      終了処理を行います.
    //-------------------------------------------------------------------------
    void Term();

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
    //! @brief      リソースを取得します.
    //!
    //! @return     リソースを返却します.
    //-------------------------------------------------------------------------
    ID3D12Resource* GetResource() const;

    //-------------------------------------------------------------------------
    //! @brief      光束の値を取得します.
    //!
    //! @return     光束の値を返却します.
    //-------------------------------------------------------------------------
    float GetLumen() const;

private:
    //=========================================================================
    // private variables.
    //=========================================================================
    Microsoft::WRL::ComPtr<ID3D12Resource>  m_Resource;     //!< リソースです.
    DescriptorHandle*                       m_pHandle;      //!< ディスクリプタハンドルです.
    DescriptorPool*                         m_pPool;        //!< ディスクリプタプールです.
    float                                   m_Lumen;        //!< 光束です.
    std::vector<float>                      m_Candera;      //!< カンデラです.

    //=========================================================================
    // private methods.
    //=========================================================================
    IESProfile              (const IESProfile&) = delete;   // アクセス禁止.
    IESProfile& operator =  (const IESProfile&) = delete;   // アクセス禁止.
};
