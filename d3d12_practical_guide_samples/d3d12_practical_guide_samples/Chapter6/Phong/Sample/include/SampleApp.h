﻿//-----------------------------------------------------------------------------
// File : SampleApp.h
// Desc : Sample Application.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <App.h>
#include <ConstantBuffer.h>
#include <Material.h>


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
    std::vector<Mesh*>              m_pMesh;            //!< メッシュです.
    std::vector<ConstantBuffer*>    m_Transform;        //!< 変換行列です.
    ConstantBuffer*                 m_pLight;           //!< ライトです.
    Material                        m_Material;         //!< マテリアルです.
    ComPtr<ID3D12PipelineState>     m_pPSO;             //!< パイプラインステートです.
    ComPtr<ID3D12RootSignature>     m_pRootSig;         //!< ルートシグニチャです.
    float                           m_RotateAngle;      //!< 回転角です.

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
};
