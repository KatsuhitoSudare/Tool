#include "..\..\KALEIDOSCOPE\include\PixelShader.h"

HRESULT PixelShader::InitPixelShader(const wchar_t* FileName, const char* EntryPoint, ID3D11Device* _device)
{
    //シェーダーをコンパイルする
    ComPtr<ID3DBlob> compiledPS;
    auto hr = D3DCompileFromFile(FileName, nullptr, nullptr, EntryPoint, "ps_5_0", 0, 0, &compiledPS, nullptr);
    if (FAILED(hr))
        return hr;

    //シェーダーを作成
    hr = _device->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &Shader);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void PixelShader::SetPixelShader(ID3D11DeviceContext* context)
{
    context->PSSetShader(Shader.Get(),NULL,0);
}
