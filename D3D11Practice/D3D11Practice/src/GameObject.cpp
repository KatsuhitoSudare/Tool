#include "GameObject.h"
#include"Direct3D11/cDirect3D.h"
#include"WICTextureLoader11.h"

//頂点の情報
D3D11_INPUT_ELEMENT_DESC desc[5] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のPOSITION
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2のTEXCOORD
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のNORMAL
	{ "BONEINDICES",    0, DXGI_FORMAT_R32G32B32A32_SINT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3のTANGENT
	{ "BONEWEIGHTS",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4のCOLOR
};

GameObject::GameObject()
{
	//頂点シェーダーの作成
	mVS.InitVertexShader(L"Shader/VertexShader.hlsl", "main", cDirect3D::GetDevice(), desc, 5);
	//ピクセルシェーダーの作成
	mPS.InitPixelShader(L"Shader/PixelShader.hlsl", "main", cDirect3D::GetDevice());
	//
	ModelLoader::LoadModel("walking.fbx",modelData);

	mVB.resize(modelData.Meshes.size());
	for (int i = 0; i < modelData.Meshes.size(); i++)
	{
		mVB[i].CreateVertexBuffer(cDirect3D::GetDevice(), cDirect3D::GetContext(), modelData.Meshes[i].vertices);
	}

	//トランスフォームの定数を作成
	mCB.CreateConstantBuffer(cDirect3D::GetDevice());

	//ボーン行列の定数を作成
	mBoneBuffer.resize(modelData.Meshes.size());
	for (int i = 0; i < modelData.Meshes.size(); i++)
	{
		mBoneBuffer[i].CreateConstantBuffer(cDirect3D::GetDevice());
	}
	

	XMVECTOR m_CameraPos = XMVectorSet(0.0f, 0.0f, -240.0f, 0.0f);
	XMVECTOR m_Camerafocus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR m_CameraTop = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//ビュー座標を初期化
	mV = XMMatrixLookAtLH(m_CameraPos, m_Camerafocus, m_CameraTop);

	mP = XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, 16.0f / 9.0f, 0.1f, 1000.0f);

	mW = XMMatrixIdentity();
}

void GameObject::Update()
{
	static float oo = 0;

	oo += 0.001;

	Constant constTransform;
	
	XMMATRIX rotatY = XMMatrixRotationY(oo);

	XMMATRIX rotatX = XMMatrixRotationX(XMConvertToRadians(0));

	XMMATRIX trans = XMMatrixTranslation(0.0f, -80.0f, 0.0f);

	mW = rotatX * rotatY * trans;

	constTransform.W = XMMatrixTranspose(mW);
	constTransform.V = XMMatrixTranspose(mV);
	constTransform.P = XMMatrixTranspose(mP);
	
	mCB.UpdateBufferResource(&constTransform, cDirect3D::GetContext());

	//ポージングアップデート
	//modelData.Meshes[13].Bones["Character1_LeftFoot"].BoneMatrix = XMMatrixTranslation(0.0f, -80.0f, 0.0f);


	for (int i = 0; i < mBoneBuffer.size(); i++)
	{
		BoneBuffer boneMatrix;
		for (int j = 0; j < modelData.Meshes[i].Bones.size(); j++)
		{
			for (auto& boneMat : modelData.Meshes[i].Bones)
			{
				boneMatrix.bone[j] = boneMat.second.BoneMatrix;
			}
		}
		mBoneBuffer[i].UpdateBufferResource(&boneMatrix, cDirect3D::GetContext());
	}
}

void GameObject::Render()
{
	static float o = 0;
	o += 0.01;
	if (modelData.Meshes.size() < o)
	{
		o = 0;
	}
	for (int i = 0; i < 1; i++)
	{
		i = (int)o;
		mVS.SetVertexShaderAndInputLayout(cDirect3D::GetContext());
		mPS.SetPixelShader(cDirect3D::GetContext());
		mCB.VSSetConstantBuffer(cDirect3D::GetContext(), 0);
		mBoneBuffer[i].VSSetConstantBuffer(cDirect3D::GetContext(),1);
		mVB[i].IASetVertexBuffer(cDirect3D::GetContext(), modelData.Meshes[i].vertices);
		//IB[i].IASetIndexBuffer(cDirect3D::GetContext());

		//cDirect3D::GetContext()->DrawIndexed(Meshes[i].Indices.size(), 0, 0);
		cDirect3D::GetContext()->Draw(modelData.Meshes[i].vertices.size() * 3, 0);
	}
}
