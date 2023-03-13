#include "VertexShader.h"


VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

HRESULT VertexShader::InitVertexShader(const wchar_t* FileName, const char* EntryPoint, ID3D11Device* _device)
{
    //シェーダーをコンパイルする
    ComPtr<ID3DBlob> compiledVS;
    auto hr =  D3DCompileFromFile(FileName, nullptr, nullptr, EntryPoint, "vs_5_0", 0, 0, &compiledVS, nullptr);
    if (FAILED(hr))
        return hr;

    //シェーダーを作成
    hr = _device->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &Shader);
    if (FAILED(hr))
        return hr;

    //インプットレイアウトの作成
    D3D11_INPUT_ELEMENT_DESC desc[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,           0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT,        0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    hr = _device->CreateInputLayout(desc, ARRAYSIZE(desc), compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &InputLayout);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void VertexShader::SetVertexShaderAndInputLayout(ID3D11DeviceContext* context)
{
    context->IASetInputLayout(InputLayout.Get());
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->VSSetShader(Shader.Get(),NULL,0);
}
