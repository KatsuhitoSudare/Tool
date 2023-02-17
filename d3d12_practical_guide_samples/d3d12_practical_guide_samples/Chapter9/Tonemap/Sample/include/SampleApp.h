﻿//-----------------------------------------------------------------------------
// File : SampleApp.h
// Desc : Sample Application.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <App.h>
#include <Camera.h>
#include <ConstantBuffer.h>


///////////////////////////////////////////////////////////////////////////////
// SampleApp class
///////////////////////////////////////////////////////////////////////////////
class SampleApp : public App
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
    //!
    //! @param[in]      width       ウィンドウの横幅です.
    //! @param[in]      height      ウィンドウの縦幅です.
    //-------------------------------------------------------------------------
    SampleApp(uint32_t width, uint32_t height);

    //-------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //-------------------------------------------------------------------------
    virtual ~SampleApp();

private:
    //=========================================================================
    // private variables.
    //=========================================================================
    ComPtr<ID3D12PipelineState>     m_pPSO;             //!< パイプラインステートです.
    ComPtr<ID3D12PipelineState>     m_pGridPSO;         //!< グリッド用パイプラインステートです.
    ComPtr<ID3D12RootSignature>     m_pRootSig;         //!< ルートシグニチャです.
    VertexBuffer                    m_QuadVB;           //!< 頂点バッファです.
    ConstantBuffer                  m_CB[FrameCount];   //!< 定数バッファです.
    Texture                         m_Texture;          //!< HDR画像.
    int                             m_TonemapType;      //!< トーンマップタイプ.
    int                             m_ColorSpace;       //!< 出力色空間
    float                           m_BaseLuminance;    //!< 基準輝度値.
    float                           m_MaxLuminance;     //!< 最大輝度値.
    float                           m_Exposure;         //!< 露光値.

    //=========================================================================
    // private methods.
    //=========================================================================

    //-------------------------------------------------------------------------
    //! @brief      初期化時の処理です.
    //!
    //! @retval true    初期化に成功.
    //! @retval false   初期化に失敗.
    //-------------------------------------------------------------------------
    bool OnInit() override;

    //-------------------------------------------------------------------------
    //! @brief      終了時の処理です.
    //-------------------------------------------------------------------------
    void OnTerm() override;

    //-------------------------------------------------------------------------
    //! @brief      描画時の処理です.
    //-------------------------------------------------------------------------
    void OnRender() override;

    //-------------------------------------------------------------------------
    //! @brief      メッセージプロシージャです.
    //-------------------------------------------------------------------------
    void OnMsgProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) override;

    //-------------------------------------------------------------------------
    //! @brief      ディスプレイモードを変更します.
    //!
    //! @param[in]      hdr     trueであればHDRディスプレイ用の設定に変更します.
    //-------------------------------------------------------------------------
    void ChangeDisplayMode(bool hdr);
};
