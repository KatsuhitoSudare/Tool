//-------------------------------------------------------------------------------------------------
// File : Gui.h
// Desc : Graphical User Interface Helper.
// Copyright(c) Pocol. All right reserved.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <Gui.h>
#include <list>
#include <Logger.h>


namespace {

#include "../res/Shader/Compiled/GuiVS.inc"
#include "../res/Shader/Compiled/GuiPS.inc"

//-------------------------------------------------------------------------------------------------
// Global Variables.
//-------------------------------------------------------------------------------------------------
std::list<Gui*> g_GuiList;      //!< GUIリストです.

} // namespace


//-------------------------------------------------------------------------------------------------
//      GUI描画処理を呼び出します.
//-------------------------------------------------------------------------------------------------
void KickDraw(ImDrawData* pData)
{
    for(auto& itr : g_GuiList)
    { itr->OnDraw(pData); }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Gui class
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//      コンストラクタです.
//-------------------------------------------------------------------------------------------------
Gui::Gui()
: m_pCmdList(nullptr)
, m_Index   (0)
{ /* DO_NOTHING */ }

//-------------------------------------------------------------------------------------------------
//      デストラクタです.
//-------------------------------------------------------------------------------------------------
Gui::~Gui()
{ Term(); }

//-------------------------------------------------------------------------------------------------
//      初期化処理を行います.
//-------------------------------------------------------------------------------------------------
bool Gui::Init(ID3D12Device* pDevice, DescriptorPool* pPool, DXGI_FORMAT format, HWND hWnd, DirectX::ResourceUploadBatch& batch)
{
    if (pDevice == nullptr || pPool == nullptr)
    { return false; }

    // 頂点バッファを生成.
    {
        for(auto i=0; i<2; ++i)
        {
            if (!m_VB[i].Init<ImDrawVert>(pDevice, MaxPrimitiveCount * 4))
            {
                ELOG("Error : VertexBuffer::Init() Failed.");
                return false;
            }
        }
    }

    // インデックスバッファを生成.
    {
        for(auto i=0; i<2; ++i)
        {
            if (!m_IB[i].Init(pDevice, MaxPrimitiveCount * 6))
            {
                ELOG("Error : IndexBuffer::Init() Failed.");
                return false;
            }
        }
    }

    // 定数バッファを生成.
    {
        for(auto i=0; i<2; ++i)
        {
            if (!m_CB[i].Init(pDevice, pPool, sizeof(float) * 16))
            {
                ELOG("Error : ConstantBuffer::Init() Failed.");
                return false;
            }
        }
    }

    auto& io = ImGui::GetIO();

    // フォントテクスチャを生成.
    {
        uint8_t* pixels = nullptr;
        int w   = 0;
        int h   = 0;
        int bpp = 0;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &w, &h, &bpp);

        auto rowPitch   = w * bpp;
        auto slicePitch = rowPitch * rowPitch;

        D3D12_RESOURCE_DESC desc = {};
        desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        desc.Alignment          = 0;
        desc.Width              = w;
        desc.Height             = h;
        desc.DepthOrArraySize   = 1;
        desc.MipLevels          = 1;
        desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count   = 1;
        desc.SampleDesc.Quality = 0;
        desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
        desc.Flags              = D3D12_RESOURCE_FLAG_NONE;

        if (!m_Font.Init(pDevice, pPool, &desc, D3D12_RESOURCE_STATE_COPY_DEST, false))
        {
            ELOG("Error : Texture::Init() Failed.");
            return false;
        }

        D3D12_SUBRESOURCE_DATA subRes = {};
        subRes.pData        = pixels;
        subRes.RowPitch     = rowPitch;
        subRes.SlicePitch   = slicePitch;

        batch.Upload(m_Font.GetResource(), 0, &subRes, 1);
        batch.Transition(
            m_Font.GetResource(),
            D3D12_RESOURCE_STATE_COPY_DEST,
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    }

    // ルートシグニチャの生成.
    {
        D3D12_STATIC_SAMPLER_DESC staticSampler = {};
        staticSampler.Filter            = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
        staticSampler.AddressU          = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        staticSampler.AddressV          = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        staticSampler.AddressW          = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        staticSampler.MipLODBias        = 0.f;
        staticSampler.MaxAnisotropy     = 0;
        staticSampler.ComparisonFunc    = D3D12_COMPARISON_FUNC_ALWAYS;
        staticSampler.BorderColor       = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
        staticSampler.MinLOD            = 0.f;
        staticSampler.MaxLOD            = 0.f;
        staticSampler.ShaderRegister    = 0;
        staticSampler.RegisterSpace     = 0;
        staticSampler.ShaderVisibility  = D3D12_SHADER_VISIBILITY_PIXEL;

        D3D12_DESCRIPTOR_RANGE descRange = {};
        descRange.RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
        descRange.NumDescriptors                    = 1;
        descRange.BaseShaderRegister                = 0;
        descRange.RegisterSpace                     = 0;
        descRange.OffsetInDescriptorsFromTableStart = 0;

        D3D12_ROOT_PARAMETER param[2] = {};

        param[0].ParameterType              = D3D12_ROOT_PARAMETER_TYPE_CBV;
        param[0].Descriptor.RegisterSpace   = 0;
        param[0].Descriptor.ShaderRegister  = 0;
        param[0].ShaderVisibility           = D3D12_SHADER_VISIBILITY_VERTEX;

        param[1].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        param[1].DescriptorTable.NumDescriptorRanges = 1;
        param[1].DescriptorTable.pDescriptorRanges   = &descRange;
        param[1].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_PIXEL;

        D3D12_ROOT_SIGNATURE_DESC desc = {};
        desc.NumParameters      = _countof(param);
        desc.pParameters        = param;
        desc.NumStaticSamplers  = 1;
        desc.pStaticSamplers    = &staticSampler;
        desc.Flags =
            D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS       |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS     |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;

        ComPtr<ID3DBlob> blob;
        auto hr = D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1, blob.GetAddressOf(), nullptr);
        if (FAILED(hr))
        {
            ELOG("Error : D3D12SerializeRootSignature() Failed. retcode = 0x%x", hr);
            return false;
        }

        hr = pDevice->CreateRootSignature(
            0,
            blob->GetBufferPointer(),
            blob->GetBufferSize(),
            IID_PPV_ARGS(m_RootSig.GetAddressOf()));
        if (FAILED(hr))
        {
            ELOG("Error : ID3D12Device::CreateRootSignature() Failed. retcode = 0x%x", hr);
            return false;
        }
    }

    // パイプラインステートの生成.
    {
        D3D12_INPUT_ELEMENT_DESC local_layout[] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (size_t)(&((ImDrawVert*)0)->pos), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (size_t)(&((ImDrawVert*)0)->uv),  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
            { "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, (size_t)(&((ImDrawVert*)0)->col), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        };

        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.NodeMask                        = 1;
        psoDesc.PrimitiveTopologyType           = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.pRootSignature                  = m_RootSig.Get();
        psoDesc.SampleMask                      = UINT_MAX;
        psoDesc.NumRenderTargets                = 1;
        psoDesc.RTVFormats[0]                   = format;
        psoDesc.SampleDesc.Count                = 1;
        psoDesc.Flags                           = D3D12_PIPELINE_STATE_FLAG_NONE;
        psoDesc.InputLayout.NumElements         = 3;
        psoDesc.InputLayout.pInputElementDescs  = local_layout;
        psoDesc.VS.BytecodeLength               = sizeof(GuiVS);
        psoDesc.VS.pShaderBytecode              = GuiVS;
        psoDesc.PS.BytecodeLength               = sizeof(GuiPS);
        psoDesc.PS.pShaderBytecode              = GuiPS;

        // Create the blending setup
        {
            D3D12_BLEND_DESC& desc = psoDesc.BlendState;
            desc.AlphaToCoverageEnable                  = false;
            desc.RenderTarget[0].BlendEnable            = true;
            desc.RenderTarget[0].SrcBlend               = D3D12_BLEND_SRC_ALPHA;
            desc.RenderTarget[0].DestBlend              = D3D12_BLEND_INV_SRC_ALPHA;
            desc.RenderTarget[0].BlendOp                = D3D12_BLEND_OP_ADD;
            desc.RenderTarget[0].SrcBlendAlpha          = D3D12_BLEND_INV_SRC_ALPHA;
            desc.RenderTarget[0].DestBlendAlpha         = D3D12_BLEND_ZERO;
            desc.RenderTarget[0].BlendOpAlpha           = D3D12_BLEND_OP_ADD;
            desc.RenderTarget[0].RenderTargetWriteMask  = D3D12_COLOR_WRITE_ENABLE_ALL;
        }

        // Create the rasterizer state
        {
            D3D12_RASTERIZER_DESC& desc = psoDesc.RasterizerState;
            desc.FillMode               = D3D12_FILL_MODE_SOLID;
            desc.CullMode               = D3D12_CULL_MODE_NONE;
            desc.FrontCounterClockwise  = FALSE;
            desc.DepthBias              = D3D12_DEFAULT_DEPTH_BIAS;
            desc.DepthBiasClamp         = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
            desc.SlopeScaledDepthBias   = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
            desc.DepthClipEnable        = true;
            desc.MultisampleEnable      = FALSE;
            desc.AntialiasedLineEnable  = FALSE;
            desc.ForcedSampleCount      = 0;
            desc.ConservativeRaster     = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
        }

        // Create depth-stencil State
        {
            D3D12_DEPTH_STENCIL_DESC& desc = psoDesc.DepthStencilState;
            desc.DepthEnable             = FALSE;
            desc.DepthWriteMask          = D3D12_DEPTH_WRITE_MASK_ALL;
            desc.DepthFunc               = D3D12_COMPARISON_FUNC_ALWAYS;
            desc.StencilEnable           = FALSE;
            desc.FrontFace.StencilFailOp = desc.FrontFace.StencilDepthFailOp = desc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
            desc.FrontFace.StencilFunc   = D3D12_COMPARISON_FUNC_ALWAYS;
            desc.BackFace                = desc.FrontFace;
        }

        auto hr = pDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(m_PSO.GetAddressOf()));
        if (FAILED(hr))
        {
            ELOG("Error : ID3D12Device::CreateGraphicsPipelineState() Failed. retcode = 0x%x", hr);
            return false;
        }
    }

    //io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;   // We can honor GetMouseCursor() values (optional)
    //io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;    // We can honor io.WantSetMousePos requests (optional, rarely used)

    io.KeyMap[ImGuiKey_Tab]         = VK_TAB;
    io.KeyMap[ImGuiKey_LeftArrow]   = VK_LEFT;
    io.KeyMap[ImGuiKey_RightArrow]  = VK_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow]     = VK_UP;
    io.KeyMap[ImGuiKey_DownArrow]   = VK_DOWN;
    io.KeyMap[ImGuiKey_PageUp]      = VK_PRIOR;
    io.KeyMap[ImGuiKey_PageDown]    = VK_NEXT;
    io.KeyMap[ImGuiKey_Home]        = VK_HOME;
    io.KeyMap[ImGuiKey_End]         = VK_END;
    //io.KeyMap[ImGuiKey_Insert]     = VK_INSERT;
    io.KeyMap[ImGuiKey_Delete]      = VK_DELETE;
    io.KeyMap[ImGuiKey_Backspace]   = VK_BACK;
    //io.KeyMap[ImGuiKey_Space]      = VK_SPACE;
    io.KeyMap[ImGuiKey_Enter]       = VK_RETURN;
    io.KeyMap[ImGuiKey_Escape]      = VK_ESCAPE;
    io.KeyMap[ImGuiKey_A]           = 'A';
    io.KeyMap[ImGuiKey_C]           = 'C';
    io.KeyMap[ImGuiKey_V]           = 'V';
    io.KeyMap[ImGuiKey_X]           = 'X';
    io.KeyMap[ImGuiKey_Y]           = 'Y';
    io.KeyMap[ImGuiKey_Z]           = 'Z';

    RECT rect;
    GetClientRect(hWnd, &rect);

    io.ImeWindowHandle      = hWnd;
    io.RenderDrawListsFn    = KickDraw;
    io.SetClipboardTextFn   = nullptr;
    io.GetClipboardTextFn   = nullptr;
    io.Fonts->TexID         = reinterpret_cast<void*>(&m_Font.GetHandleGPU());
    io.IniFilename          = nullptr;
    io.LogFilename          = nullptr;
    io.Framerate            = 0.5f;
    io.DisplaySize.x        = float(rect.right - rect.left);
    io.DisplaySize.y        = float(rect.bottom - rect.top);

    auto& style = ImGui::GetStyle();
    style.WindowRounding = 2.0f;
    style.ChildRounding  = 2.0f;

    // GUIリストに登録.
    g_GuiList.push_back(this);

    m_LastTime = std::chrono::system_clock::now();

    // 正常終了.
    return true;
}

//-------------------------------------------------------------------------------------------------
//      終了処理を行います.
//-------------------------------------------------------------------------------------------------
void Gui::Term()
{
    for(auto i=0; i<2; ++i)
    { 
        m_CB[i].Term();
        m_VB[i].Term();
        m_IB[i].Term();
    }

    m_Font   .Term();
    m_RootSig.Reset();
    m_PSO    .Reset();
    m_pCmdList  = nullptr;
    m_Index     = 0;

    // GUIリストから登録解除.
    g_GuiList.remove(this);
}

//-------------------------------------------------------------------------------------------------
//      描画処理を行います.
//-------------------------------------------------------------------------------------------------
void Gui::Draw(ID3D12GraphicsCommandList* pCmdList)
{
    m_pCmdList = pCmdList;

    ImGui::Render();
}

//-------------------------------------------------------------------------------------------------
//      描画コマンドを生成します.
//-------------------------------------------------------------------------------------------------
void Gui::OnDraw(ImDrawData* pData)
{
    auto& io = ImGui::GetIO();

    {
        auto w = static_cast<int>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
        auto h = static_cast<int>(io.DisplaySize.y * io.DisplayFramebufferScale.y);

        // レンダーターゲットサイズが0であれば描画しない.
        if (w == 0 || h == 0)
        { return; }
    }

    // 最大サイズを超える場合は描画せずに終了.
    if (size_t(pData->TotalVtxCount) >= MaxPrimitiveCount * 4
     || size_t(pData->TotalIdxCount) >= MaxPrimitiveCount * 6)
    { return; }

    auto vtxSize = pData->TotalVtxCount * sizeof(ImDrawVert);
    auto idxSize = pData->TotalVtxCount * sizeof(ImDrawIdx);

    // 頂点バッファとインデックスバッファの更新処理.
    {
        auto pVtxDst = m_VB[m_Index].Map<ImDrawVert>();
        auto pIdxDst = m_IB[m_Index].Map();

        for (auto n = 0; n < pData->CmdListsCount; ++n)
        {
            const auto pList = pData->CmdLists[n];
            memcpy(pVtxDst, &pList->VtxBuffer[0], pList->VtxBuffer.size() * sizeof(ImDrawVert));

            // データサイズが異なるのでキャストが必要.
            for (auto i = 0; i < pList->IdxBuffer.size(); ++i)
            { pIdxDst[i] = static_cast<uint32_t>(pList->IdxBuffer[i]); }

            pVtxDst += pList->VtxBuffer.size();
            pIdxDst += pList->IdxBuffer.size();
        }

        m_VB[m_Index].Unmap();
        m_IB[m_Index].Unmap();
    }

    // 定数バッファを更新.
    {
        float L = 0.0f;
        float R = ImGui::GetIO().DisplaySize.x;
        float B = ImGui::GetIO().DisplaySize.y;
        float T = 0.0f;
        float mvp[4][4] =
        {
            { 2.0f/(R-L),   0.0f,           0.0f,       0.0f },
            { 0.0f,         2.0f/(T-B),     0.0f,       0.0f },
            { 0.0f,         0.0f,           0.5f,       0.0f },
            { (R+L)/(L-R),  (T+B)/(B-T),    0.5f,       1.0f },
        };

        auto ptr = m_CB[m_Index].GetPtr();
        memcpy( ptr, mvp, sizeof(float) * 16 );
    }

    // パイプラインステート等の設定.
    {
        D3D12_VIEWPORT viewport = {};
        viewport.TopLeftX   = 0;
        viewport.TopLeftY   = 0;
        viewport.Width      = io.DisplaySize.x;
        viewport.Height     = io.DisplaySize.y;
        viewport.MinDepth   = 0.0f;
        viewport.MaxDepth   = 1.0f;

        m_pCmdList->RSSetViewports(1, &viewport);

        auto vbv = m_VB[m_Index].GetView();
        auto ibv = m_IB[m_Index].GetView();
        m_pCmdList->SetGraphicsRootSignature(m_RootSig.Get());
        m_pCmdList->SetPipelineState(m_PSO.Get());
        m_pCmdList->SetGraphicsRootConstantBufferView( 0, m_CB[m_Index].GetAddress() );
        m_pCmdList->SetGraphicsRootDescriptorTable( 1, m_Font.GetHandleGPU() );
        m_pCmdList->IASetVertexBuffers(0, 1, &vbv);
        m_pCmdList->IASetIndexBuffer(&ibv);
    }

    // 描画コマンドを生成.
    {
        auto vtxOffset = 0;
        auto idxOffset = 0;

        for (auto n = 0; n < pData->CmdListsCount; ++n)
        {
            const auto pList = pData->CmdLists[n];
            for (auto i = 0; i < pList->CmdBuffer.size(); ++i)
            {
                auto pCmd = &pList->CmdBuffer[i];
                if (pCmd->UserCallback)
                { pCmd->UserCallback(pList, pCmd); }
                else
                {
                    auto left   = static_cast<LONG>(pCmd->ClipRect.x);
                    auto top    = static_cast<LONG>(pCmd->ClipRect.y);
                    auto right  = static_cast<LONG>(pCmd->ClipRect.z);
                    auto bottom = static_cast<LONG>(pCmd->ClipRect.w);

                    D3D12_RECT scissor = {};
                    scissor.left    = left;
                    scissor.top     = top;
                    scissor.right   = right;
                    scissor.bottom  = bottom;

                    m_pCmdList->RSSetScissorRects(1, &scissor);
                    m_pCmdList->DrawIndexedInstanced(pCmd->ElemCount, 1, idxOffset, vtxOffset, 0);
                }
                idxOffset += pCmd->ElemCount;
            }
            vtxOffset += pList->VtxBuffer.size();
        }
    }
}

//-------------------------------------------------------------------------------------------------
//      バッファを入れ替えます.
//-------------------------------------------------------------------------------------------------
void Gui::SwapBuffers()
{
    auto time = std::chrono::system_clock::now();
    auto elapsedMilliSec = std::chrono::duration_cast<std::chrono::milliseconds>(time - m_LastTime).count();
    auto elapsedSec      = float(elapsedMilliSec / 1000.0);

    auto& io = ImGui::GetIO();
    io.DeltaTime = elapsedSec;
    io.KeyCtrl   = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
    io.KeyShift  = (GetKeyState(VK_SHIFT)   & 0x8000) != 0;
    io.KeyAlt    = (GetKeyState(VK_MENU)    & 0x8000) != 0;
    io.KeySuper  = false;

    m_Index = (m_Index + 1) % 2;
    ImGui::NewFrame();

    m_LastTime = time;
}

//-------------------------------------------------------------------------------------------------
//      ウィンドウメッセージを処理します.
//-------------------------------------------------------------------------------------------------
void Gui::MsgProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
   if (ImGui::GetCurrentContext() == nullptr)
   { return; }

    auto& io = ImGui::GetIO();

    switch (msg)
    {
        case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
            {
                int button = 0;
                if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) button = 0;
                if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) button = 1;
                if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) button = 2;
                if (::GetCapture() == NULL)
                { ::SetCapture(hWnd); }
                io.MouseDown[button] = true;
            }
            break;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            {
                int button = 0;
                if (msg == WM_LBUTTONUP) button = 0;
                if (msg == WM_RBUTTONUP) button = 1;
                if (msg == WM_MBUTTONUP) button = 2;
                io.MouseDown[button] = false;
                if (::GetCapture() == hWnd)
                { ::ReleaseCapture(); }
            }
            break;

        case WM_MOUSEWHEEL:
            {
                if (wp == 0)
                { io.MouseWheel = 0; }
                else if ( GET_WHEEL_DELTA_WPARAM(wp) > 0)
                { io.MouseWheel = 1.0f; }
                else if ( GET_WHEEL_DELTA_WPARAM(wp) < 0)
                { io.MouseWheel = -1.0f; }
            }
            break;

        case WM_MOUSEMOVE:
            {
                io.MousePos.x = static_cast<signed short>(lp);
                io.MousePos.y = static_cast<signed short>(lp >> 16);
            }
            break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            {
                if (wp < 256)
                    io.KeysDown[wp] = true;
            }
            break;

        case WM_KEYUP:
        case WM_SYSKEYUP:
            {
                if (wp < 256)
                    io.KeysDown[wp] = false;
            }
            break;

       case WM_CHAR:
           {
                // You can also use ToAscii()+GetKeyboardState() to retrieve characters.
                if (wp > 0 && wp < 0x10000)
                { io.AddInputCharacter(static_cast<unsigned short>(wp)); }
           }
           break;

       case WM_SIZE:
          {
                auto w = LOWORD(lp);
                auto h = HIWORD(lp);
                if (w < 0)
                { w = 1; }
                if (h < 0)
                { h = 1; }

                io.DisplaySize.x = float(w);
                io.DisplaySize.y = float(h);
          }
          break;

       default:
           break;
    }
}