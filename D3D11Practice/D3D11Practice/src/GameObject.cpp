#include "GameObject.h"
#include"Direct3D11/cDirect3D.h"

//頂点の情報
D3D11_INPUT_ELEMENT_DESC desc[5] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のPOSITION
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のNORMAL
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2のTEXCOORD
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のTANGENT
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4のCOLOR
};

GameObject::GameObject()
{
	//頂点シェーダーの作成
	mVS.InitVertexShader(L"Shader/VertexShader.hlsl", "vert", cDirect3D::GetDevice(), desc, 5);
	//ピクセルシェーダーの作成
	mPS.InitPixelShader(L"Shader/PixelShader.hlsl", "pixel", cDirect3D::GetDevice());
	//
	ModelLoader::LoadModel("Alicia.fbx",modelData);
}
