#include "PixelShader.h"
#include"cDirect3D.h"

HRESULT PixelShader::InitPixelShader(const wchar_t* FileName)
{
    //�V�F�[�_�[���R���p�C������
    ComPtr<ID3DBlob> compiledPS;
    auto hr = D3DCompileFromFile(FileName, nullptr, nullptr, "main", "ps_5_0", 0, 0, &compiledPS, nullptr);
    if (FAILED(hr))
        return hr;

    //�V�F�[�_�[���쐬
    hr = cDirect3D::GetDevice()->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &Shader);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void PixelShader::SetPixelShader()
{
    cDirect3D::GetContext()->PSSetShader(Shader.Get(), NULL, 0);
}
