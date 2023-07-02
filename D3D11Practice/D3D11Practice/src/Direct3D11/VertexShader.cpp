#include "VertexShader.h"
#include<d3d11.h>
#include"cDirect3D.h"

//���_�̏��
D3D11_INPUT_ELEMENT_DESC desc[3] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��POSITION
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2��TEXCOORD
    { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��NORMAL
};

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

HRESULT VertexShader::InitVertexShader(const wchar_t* FileName)
{
    //�V�F�[�_�[���R���p�C������
    ComPtr<ID3DBlob> compiledVS;
    auto hr =  D3DCompileFromFile(FileName, nullptr, nullptr, "main", "vs_5_0", 0, 0, &compiledVS, nullptr);
    if (FAILED(hr))
        return hr;

    //�V�F�[�_�[���쐬
    hr = cDirect3D::GetDevice()->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &Shader);
    if (FAILED(hr))
        return hr;

    hr = cDirect3D::GetDevice()->CreateInputLayout(desc, 3, compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &InputLayout);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void VertexShader::SetVertexShaderAndInputLayout()
{
    cDirect3D::GetContext()->IASetInputLayout(InputLayout.Get());
    cDirect3D::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    cDirect3D::GetContext()->VSSetShader(Shader.Get(),NULL,0);
}
