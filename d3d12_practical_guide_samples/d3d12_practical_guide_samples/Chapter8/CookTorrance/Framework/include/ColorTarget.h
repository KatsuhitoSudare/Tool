﻿//-----------------------------------------------------------------------------
// File : ColorTarget.h
// Desc : Color Target Module.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <d3d12.h>
#include <dxgi1_6.h>
#include <ComPtr.h>
#include <cstdint>


//-----------------------------------------------------------------------------
// Forward Declarations.
//-----------------------------------------------------------------------------
class DescriptorHandle;
class DescriptorPool;


///////////////////////////////////////////////////////////////////////////////
// ColorTarget class
///////////////////////////////////////////////////////////////////////////////
class ColorTarget
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
    ColorTarget();

    //-------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //-------------------------------------------------------------------------
    ~ColorTarget();

    //-------------------------------------------------------------------------
    //! @brief      初期化処理を行います.
    //!
    //! @param[in]      pDevice     デバイスです.
    //! @param[in]      pPoolRTV    ディスクリプタプールです.
    //! @param[in]      width       横幅です.
    //! @param[in]      height      縦幅です.
    //! @param[in]      format      ピクセルフォーマットです.
    //! @param[in]      useSRGB     sRGBフォーマットを使用する場合は true を指定.
    //! @retval true    初期化に成功.
    //! @retval false   初期化に失敗.
    //-------------------------------------------------------------------------
    bool Init(
        ID3D12Device*   pDevice, 
        DescriptorPool* pPoolRTV,
        uint32_t        width,
        uint32_t        height,
        DXGI_FORMAT     format,
        bool            useSRGB);

    //-------------------------------------------------------------------------
    //! @brief      バックバッファから初期化処理を行います.
    //!
    //! @param[in]      pDevice     デバイスです.
    //! @param[in]      pPoolRTV    ディスクリプタプールです.
    //! @param[in]      useSRGB     sRGBフォーマットを使用する場合は true を指定.
    //! @param[in]      index       バックバッファ番号です.
    //! @param[in]      pSwapChain  スワップチェインです.
    //! @retval true    初期化に成功.
    //! @retval false   初期化に失敗.
    //-------------------------------------------------------------------------
    bool InitFromBackBuffer(
        ID3D12Device*   pDevice,
        DescriptorPool* pPoolRTV,
        bool            useSRGB,
        uint32_t        index,
        IDXGISwapChain* pSwapChain);

    //-------------------------------------------------------------------------
    //! @brief      終了処理を行います.
    //-------------------------------------------------------------------------
    void Term();

    //-------------------------------------------------------------------------
    //! @brief      ディスクリプタハンドル(RTV用)を取得します.
    //!
    //! @return     ディスクリプタハンドル(RTV用)を返却します.
    //-------------------------------------------------------------------------
    DescriptorHandle* GetHandleRTV() const;

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
    //! @brief      レンダーターゲットビューの設定を取得します.
    //!
    //! @return     レンダーターゲットビューの設定を返却します.
    //-------------------------------------------------------------------------
    D3D12_RENDER_TARGET_VIEW_DESC GetViewDesc() const;

private:
    //=========================================================================
    // private variables.
    //=========================================================================
    ComPtr<ID3D12Resource>          m_pTarget;          //!< リソースです.
    DescriptorHandle*               m_pHandleRTV;       //!< ディスクリプタハンドル(RTV用)です.
    DescriptorPool*                 m_pPoolRTV;         //!< ディスクリプタプール(RTV用)です.
    D3D12_RENDER_TARGET_VIEW_DESC   m_ViewDesc;         //!< レンダーターゲットビューの構成です.

    //=========================================================================
    // private methods.
    //=========================================================================
    ColorTarget     (const ColorTarget&) = delete;
    void operator = (const ColorTarget&) = delete;
};