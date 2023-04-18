#include "GameObject.h"
#include"Direct3D11/cDirect3D.h"

//���_�̏��
D3D11_INPUT_ELEMENT_DESC desc[5] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��POSITION
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��NORMAL
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2��TEXCOORD
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��TANGENT
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4��COLOR
};

GameObject::GameObject()
{
	//���_�V�F�[�_�[�̍쐬
	mVS.InitVertexShader(L"Shader/VertexShader.hlsl", "vert", cDirect3D::GetDevice(), desc, 5);
	//�s�N�Z���V�F�[�_�[�̍쐬
	mPS.InitPixelShader(L"Shader/PixelShader.hlsl", "pixel", cDirect3D::GetDevice());
	//
	ModelLoader::LoadModel("Alicia.fbx",modelData);
}
