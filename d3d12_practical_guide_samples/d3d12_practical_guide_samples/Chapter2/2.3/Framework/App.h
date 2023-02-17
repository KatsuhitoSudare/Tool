//-----------------------------------------------------------------------------
// File : App.h
// Desc : Application Module.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>    // ★追加
#include <dxgi1_4.h>  // ★追加

//-----------------------------------------------------------------------------
// Linker
//-----------------------------------------------------------------------------
#pragma comment( lib, "d3d12.lib" )  // ★追加
#pragma comment( lib, "dxgi.lib" )   // ★追加


///////////////////////////////////////////////////////////////////////////////
// App class
///////////////////////////////////////////////////////////////////////////////
class App
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
    App(uint32_t width, uint32_t height);
    ~App();
    void Run();

private:
    //=========================================================================
    // private variables.
    //=========================================================================
    static const uint32_t FrameCount = 2;   // ★追加 : フレームバッファ数です.

    HINSTANCE   m_hInst;        // インスタンスハンドルです.
    HWND        m_hWnd;         // ウィンドウハンドルです.
    uint32_t    m_Width;        // ウィンドウの横幅です.
    uint32_t    m_Height;       // ウィンドウの縦幅です.

    ID3D12Device*                   m_pDevice;                      // ★追加 : デバイスです.
    ID3D12CommandQueue*             m_pQueue;                       // ★追加 : コマンドキューです.
    IDXGISwapChain3*                m_pSwapChain;                   // ★追加 : スワップチェインです.
    ID3D12Resource*                 m_pColorBuffer[FrameCount];     // ★追加 : カラーバッファです.
    ID3D12CommandAllocator*         m_pCmdAllocator[FrameCount];    // ★追加 : コマンドアロケータです.
    ID3D12GraphicsCommandList*      m_pCmdList;                     // ★追加 : コマンドリストです.
    ID3D12DescriptorHeap*           m_pHeapRTV;                     // ★追加 : ディスクリプタヒープです(レンダーターゲットビュー).
    ID3D12Fence*                    m_pFence;                       // ★追加 : フェンスです.
    HANDLE                          m_FenceEvent;                   // ★追加 : フェンスイベントです.
    uint64_t                        m_FenceCounter[FrameCount];     // ★追加 : フェンスカウンターです.
    uint32_t                        m_FrameIndex;                   // ★追加 : フレーム番号です.
    D3D12_CPU_DESCRIPTOR_HANDLE     m_HandleRTV[FrameCount];        // ★追加 : CPUディスクリプタ(レンダーターゲットビュー)です.
 
    //=========================================================================
    // private methods.
    //=========================================================================
    bool InitApp();
    void TermApp();
    bool InitWnd();
    void TermWnd();
    void MainLoop();
    bool InitD3D();  // ★追加
    void TermD3D();  // ★追加
    void Render();   // ★追加
    void WaitGpu();  // ★追加
    void Present(uint32_t interval); // ★追加

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};