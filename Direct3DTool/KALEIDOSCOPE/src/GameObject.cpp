#include "GameObject.h"
#include"cDirect3D.h"

#ifdef _DEBUG
#pragma comment(lib,"Direct3D11_debug.lib")
#else
#pragma comment(lib,"Direct3D11.lib")
#endif // _DEBUG

std::vector<Mesh> Meshes;

const wchar_t* modelFile = L"assets/Dragon 2.5_fbx.fbx";

//頂点の情報
D3D11_INPUT_ELEMENT_DESC desc[5] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のPOSITION
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のNORMAL
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2のTEXCOORD
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のTANGENT
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4のCOLOR
};

void GameObject::Init()
{
	ImportSettings importSetting = // これ自体は自作の読み込み設定構造体
	{
		modelFile,
		Meshes,
		false,
		true
	};

	//頂点シェーダーの作成
	VS.InitVertexShader(L"Shader/VertexShader.hlsl", "vert", cDirect3D::GetDevice(), desc, 5);
	//ピクセルシェーダーの作成
	PS.InitPixelShader(L"Shader/PixelShader.hlsl", "pixel", cDirect3D::GetDevice());

	AssimpLoader::Load(importSetting);


	//頂点バッファの作成
	VB.resize(Meshes.size());
	//メッシュの数だけ頂点バッファを作成する
	for (int i = 0; i < Meshes.size(); i++)
	{
		VB[i].CreateVertexBuffer(cDirect3D::GetDevice(),cDirect3D::GetContext(), Meshes[i].Vertices);
	}

	//インデックスバッファの作成
	IB.resize(Meshes.size());
	for (int i = 0; i < Meshes.size(); i++)
	{
		IB[i].CreateIndexBuffer(cDirect3D::GetDevice(), Meshes[i].Indices);
	}

	//定数バッファの作成
	CB.CreateConstantBuffer(cDirect3D::GetDevice());
	
	XMVECTOR m_CameraPos = XMVectorSet(0.0f, 0.0f, -120-.0f, 0.0f);
	XMVECTOR m_Camerafocus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR m_CameraTop = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//ビュー座標を初期化
	mV = XMMatrixLookAtLH(m_CameraPos, m_Camerafocus, m_CameraTop);
	
	mP = XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, 16.0f / 9.0f, 0.1f, 1000.0f);

	mW = XMMatrixIdentity();
}

void GameObject::Draw()
{
	Constant constant;

	constant.W = XMMatrixTranspose(mW);
	constant.V = XMMatrixTranspose(mV);
	constant.P = XMMatrixTranspose(mP);

	CB.UpdateBufferResource(&constant, cDirect3D::GetContext());

	for (int i = 0; i < Meshes.size(); i++)
	{
		VS.SetVertexShaderAndInputLayout(cDirect3D::GetContext());
		PS.SetPixelShader(cDirect3D::GetContext());
		CB.VSSetConstantBuffer(cDirect3D::GetContext(), 1);

		VB[i].IASetVertexBuffer(cDirect3D::GetContext(),Meshes[i].Vertices);
		//IB[i].IASetIndexBuffer(cDirect3D::GetContext());

		//cDirect3D::GetContext()->DrawIndexed(Meshes[i].Indices.size(), 0, 0);
		cDirect3D::GetContext()->Draw(Meshes[i].Vertices.size()*3, 0);
	}

}
