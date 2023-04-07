#include "VertexShader.h"
#include<d3d11.h>

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

HRESULT VertexShader::InitVertexShader(const wchar_t* FileName, const char* EntryPoint, ID3D11Device* _device, D3D11_INPUT_ELEMENT_DESC* desc,int descsize)
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

    hr = _device->CreateInputLayout(desc, descsize, compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &InputLayout);
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
