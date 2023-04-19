#include "GameObject.h"
#include"Direct3D11/cDirect3D.h"

//���_�̏��
D3D11_INPUT_ELEMENT_DESC desc[5] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��POSITION
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2��TEXCOORD
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��NORMAL
	{ "BONEINDICES",    0, DXGI_FORMAT_R32G32B32A32_SINT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��TANGENT
	{ "BONEWEIGHTS",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4��COLOR
};

GameObject::GameObject()
{
	//���_�V�F�[�_�[�̍쐬
	mVS.InitVertexShader(L"Shader/VertexShader.hlsl", "main", cDirect3D::GetDevice(), desc, 5);
	//�s�N�Z���V�F�[�_�[�̍쐬
	mPS.InitPixelShader(L"Shader/PixelShader.hlsl", "main", cDirect3D::GetDevice());
	//
	ModelLoader::LoadModel("Alicia.fbx",modelData);

	mVB.resize(modelData.Meshes.size());
	for (int i = 0; i < modelData.Meshes.size(); i++)
	{
		mVB[i].CreateVertexBuffer(cDirect3D::GetDevice(), cDirect3D::GetContext(), modelData.Meshes[i].vertices);
	}

	//�g�����X�t�H�[���̒萔���쐬
	mCB.CreateConstantBuffer(cDirect3D::GetDevice());

	//�{�[���s��̒萔���쐬
	mBoneBuffer.resize(modelData.Meshes.size());
	for (int i = 0; i < modelData.Meshes.size(); i++)
	{
		mBoneBuffer[i].CreateConstantBuffer(cDirect3D::GetDevice());
	}
	

	XMVECTOR m_CameraPos = XMVectorSet(0.0f, 0.0f, -180.0f, 0.0f);
	XMVECTOR m_Camerafocus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR m_CameraTop = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//�r���[���W��������
	mV = XMMatrixLookAtLH(m_CameraPos, m_Camerafocus, m_CameraTop);

	mP = XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, 16.0f / 9.0f, 0.1f, 1000.0f);

	mW = XMMatrixIdentity();

	for (int i = 0; i < mBoneBuffer.size(); i++)
	{
		BoneBuffer boneMatrix;
		for (int j = 0; j < modelData.Meshes[i].Bones.size(); j++)
		{
			for (auto boneMat : modelData.Meshes[i].Bones)
			{
				boneMatrix.bone[j] = boneMat.second.BoneMatrix;
			}
		}
		mBoneBuffer[i].UpdateBufferResource(&boneMatrix, cDirect3D::GetContext());
	}
}

void GameObject::Update()
{
	static float oo = 0;

	oo += 0.001;

	Constant constTransform;
	
	XMMATRIX rotatY = XMMatrixRotationY(oo);

	XMMATRIX rotatX = XMMatrixRotationX(XMConvertToRadians(90));

	XMMATRIX trans = XMMatrixTranslation(0.0f, -80.0f, 0.0f);

	mW = rotatX * rotatY * trans;

	constTransform.W = XMMatrixTranspose(mW);
	constTransform.V = XMMatrixTranspose(mV);
	constTransform.P = XMMatrixTranspose(mP);
	
	mCB.UpdateBufferResource(&constTransform, cDirect3D::GetContext());

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
	for (int i = 0; i < modelData.Meshes.size(); i++)
	{
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
