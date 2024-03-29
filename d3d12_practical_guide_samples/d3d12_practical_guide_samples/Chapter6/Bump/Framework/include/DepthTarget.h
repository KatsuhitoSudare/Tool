﻿//-----------------------------------------------------------------------------
// File : DepthTarget.h
// Desc : Depth Target Module.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <d3d12.h>
#include <ComPtr.h>
#include <cstdint>


//-----------------------------------------------------------------------------
// Forward Declarations.
//-----------------------------------------------------------------------------
class DescriptorHandle;
class DescriptorPool;


///////////////////////////////////////////////////////////////////////////////
// DepthTarget class
///////////////////////////////////////////////////////////////////////////////
class DepthTarget
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
    DepthTarget();

    //-------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //-------------------------------------------------------------------------
    ~DepthTarget();

    //-------------------------------------------------------------------------
    //! @brief      初期化処理を行います.
    //!
    //! @param[in]      pDevice     デバイスです.
    //! @param[in]      pPoolDSV    ディスクリプタプールです.
    //! @param[in]      width       横幅です.
    //! @param[in]      height      縦幅です.
    //! @param[in]      format      ピクセルフォーマットです.
    //! @retval true    初期化に成功.
    //! @retval false   初期化に失敗.
    //-------------------------------------------------------------------------
    bool Init(
        ID3D12Device*   pDevice, 
        DescriptorPool* pPoolDSV,
        uint32_t        width,
        uint32_t        height,
        DXGI_FORMAT     format);

    //-------------------------------------------------------------------------
    //! @brief      終了処理を行います.
    //-------------------------------------------------------------------------
    void Term();

    //-------------------------------------------------------------------------
    //! @brief      ディスクリプタハンドル(DSV用)を取得します.
    //!
    //! @return     ディスクリプタハンドル(DSV用)を返却します.
    //-------------------------------------------------------------------------
    DescriptorHandle* GetHandleDSV() const;

    //-------------------------------------------------------------------------
    //! @brief      リソースを取得します.
    //!
    //! @return     リソースを返却します.
    //-------------------------------------------------------------------------
    ID3D12Resource* GetResource() const;

    //-------------------------------------------------------------------------
    //! @brief      リソース設定を取得します.
    //!
    //! @return     リソース設定を返却します.
    //-------------------------------------------------------------------------
    D3D12_RESOURCE_DESC GetDesc() const;

    //-------------------------------------------------------------------------
    //! @brief      深度ステンシルビューの設定を取得します.
    //!
    //! @return     深度ステンシルビューの設定を返却します.
    //-------------------------------------------------------------------------
    D3D12_DEPTH_STENCIL_VIEW_DESC GetViewDesc() const;

private:
    //=========================================================================
    // private variables.
    //=========================================================================
    ComPtr<ID3D12Resource>          m_pTarget;          //!< リソースです.
    DescriptorHandle*               m_pHandleDSV;       //!< ディスクリプタハンドル(DSV用)です.
    DescriptorPool*                 m_pPoolDSV;         //!< ディスクリプタプール(DSV用)です.
    D3D12_DEPTH_STENCIL_VIEW_DESC   m_ViewDesc;         //!< 深度ステンシルビューの設定です.

    //=========================================================================
    // private methods.
    //=========================================================================
    DepthTarget     (const DepthTarget&) = delete;
    void operator = (const DepthTarget&) = delete;
};