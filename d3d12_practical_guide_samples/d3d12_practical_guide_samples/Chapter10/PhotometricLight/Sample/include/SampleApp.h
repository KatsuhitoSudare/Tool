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
#include <Material.h>
#include <IESProfile.h>
#include <RootSignature.h>


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
    ComPtr<ID3D12PipelineState>     m_pScenePSO;                    //!< シーン用パイプラインステートです.
    RootSignature                   m_SceneRootSig;                 //!< シーン用ルートシグニチャです.
    ComPtr<ID3D12PipelineState>     m_pTonemapPSO;                  //!< トーンマップ用パイプラインステートです.
    RootSignature                   m_TonemapRootSig;               //!< トーンマップ用ルートシグニチャです.
    ColorTarget                     m_SceneColorTarget;             //!< シーン用レンダーターゲットです.
    DepthTarget                     m_SceneDepthTarget;             //!< シーン用深度ターゲットです.
    VertexBuffer                    m_QuadVB;                       //!< 頂点バッファです.
    VertexBuffer                    m_WallVB;                       //!< 壁用頂点バッファです.
    VertexBuffer                    m_FloorVB;                      //!< 床用
    ConstantBuffer                  m_TonemapCB[FrameCount];        //!< 定数バッファです.
    ConstantBuffer                  m_LightCB[FrameCount];          //!< ライトバッファです.
    ConstantBuffer                  m_CameraCB[FrameCount];         //!< カメラバッファです.
    ConstantBuffer                  m_TransformCB[FrameCount];      //!< 変換用バッファです.
    ConstantBuffer                  m_MeshCB[FrameCount];           //!< メッシュ用バッファです.
    std::vector<Mesh*>              m_pMesh;                        //!< メッシュです.
    Material                        m_Material;                     //!< マテリアルです.
    float                           m_RotateAngle;                  //!< ライトの回転角です.
    int                             m_TonemapType;                  //!< トーンマップタイプ.
    int                             m_ColorSpace;                   //!< 出力色空間
    float                           m_BaseLuminance;                //!< 基準輝度値.
    float                           m_MaxLuminance;                 //!< 最大輝度値.
    float                           m_Exposure;                     //!< 露光値.
    IESProfile                      m_IESProfile;                   //!< IESプロファイルです.

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

    //-------------------------------------------------------------------------
    //! @brief      シーンを描画します.
    //-------------------------------------------------------------------------
    void DrawScene(ID3D12GraphicsCommandList* pCmdList);

    //-------------------------------------------------------------------------
    //! @brief      トーンマップを適用します.
    //-------------------------------------------------------------------------
    void DrawTonemap(ID3D12GraphicsCommandList* pCmdList);

    //-------------------------------------------------------------------------
    //! @brief      メッシュを描画します.
    //-------------------------------------------------------------------------
    void DrawMesh(ID3D12GraphicsCommandList* pCmdList);
};
