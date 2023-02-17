#pragma once
#include<Windows.h>
#include<tchar.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include<vector>

#include<d3dcompiler.h>
#include<wrl/client.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

using Microsoft::WRL::ComPtr;

class Direct3D12
{
public:
    //初期化関数
	static BOOL InitD3D12(HWND _hWmd);

    //バッファを交換する
    static void Present(uint32_t vsync);

    //レンダーターゲットのクリア
    static void CreaterRTV(float R,float G,float B);

    //深度ステンシルビューとバッファのクリア
    static void CreaterDSV();

    //コマンドの記録を開始する関数:描画の処理の前に行う
    static void StartRecordCommand();



private:
    static const uint32_t FrameCount = 2;   // フレームバッファ数です.

    static inline ComPtr<ID3D12Device>                   m_pDevice;                      // デバイスです.
    static inline ComPtr<ID3D12CommandQueue>             m_pQueue;                       // コマンドキューです.
    static inline ComPtr<IDXGISwapChain3>                m_pSwapChain;                   // スワップチェインです.
    static inline ComPtr<ID3D12Resource>                 m_pColorBuffer[FrameCount];     // カラーバッファです.
    static inline ComPtr<ID3D12Resource>                 m_pDepthBuffer;                 // 深度ステンシルバッファです.
    static inline ComPtr<ID3D12CommandAllocator>         m_pCmdAllocator[FrameCount];    // コマンドアロケータです.
    static inline ComPtr<ID3D12GraphicsCommandList>      m_pCmdList;                     // コマンドリストです.
    static inline ComPtr<ID3D12DescriptorHeap>           m_pHeapRTV;                     // ディスクリプタヒープです(レンダーターゲットビュー).
    static inline ComPtr<ID3D12DescriptorHeap>           m_pHeapDSV;
    static inline ComPtr<ID3D12Fence>                    m_pFence;                       // フェンスです.
    static inline ComPtr<ID3D12DescriptorHeap>           m_pHeapCBV_SRV_UAV;             // ★変更:ディスクリプタヒープです(定数バッファビュー・シェーダリソースビュー・アンオーダードアクセスビュー)
    static inline ComPtr<ID3D12Resource>                 m_pVB;                          // 頂点バッファです.
    static inline ComPtr<ID3D12Resource>                 m_pIB;                          // インデックスバッファです.
    static inline ComPtr<ID3D12Resource>                 m_pCB[FrameCount * 2];          // 定数バッファです.
    static inline ComPtr<ID3D12RootSignature>            m_pRootSignature;               // ルートシグニチャです.
    static inline ComPtr<ID3D12PipelineState>            m_pPSO;                         // パイプラインステートです.
    static inline HANDLE                                 m_FenceEvent;                   // フェンスイベントです.
    static inline uint64_t                               m_FenceCounter[FrameCount];     // フェンスカウンターです.
    static inline uint32_t                               m_FrameIndex;                   // フレーム番号です.
    static inline D3D12_CPU_DESCRIPTOR_HANDLE            m_HandleDSV;                    // CPUディスクリプタ(深度ステンシルビュー)です.   
    static inline D3D12_CPU_DESCRIPTOR_HANDLE            m_HandleRTV[FrameCount];        // CPUディスクリプタ(レンダーターゲットビュー)です.
    static inline D3D12_VERTEX_BUFFER_VIEW               m_VBV;                          // 頂点バッファビューです.
    static inline D3D12_INDEX_BUFFER_VIEW                m_IBV;                          // インデックスバッファビューです.
    static inline D3D12_VIEWPORT                         m_Viewport;                     // ビューポートです.
    static inline D3D12_RECT                             m_Scissor;                      // シザー矩形です.

};

