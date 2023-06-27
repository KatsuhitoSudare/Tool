#include "GameObject.h"
#include"Direct3D11/cDirect3D.h"
#include"WICTextureLoader11.h"

//���_�̏��
D3D11_INPUT_ELEMENT_DESC desc[3] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��POSITION
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2��TEXCOORD
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��NORMAL
};

GameObject::GameObject()
{
	//���_�V�F�[�_�[�̍쐬
	mVS.InitVertexShader(L"Shader/VertexShader.hlsl", "main", cDirect3D::GetDevice(), desc, 3);
	//�s�N�Z���V�F�[�_�[�̍쐬
	mPS.InitPixelShader(L"Shader/PixelShader.hlsl", "main", cDirect3D::GetDevice());

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
	

	XMVECTOR m_CameraPos = XMVectorSet(0.0f, 100.0f, -240.0f, 0.0f);
	XMVECTOR m_Camerafocus = XMVectorSet(0.0f, 100.0f, 0.0f, 0.0f);
	XMVECTOR m_CameraTop = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//�r���[���W��������
	mV = XMMatrixLookAtLH(m_CameraPos, m_Camerafocus, m_CameraTop);

	mP = XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, 16.0f / 9.0f, 0.1f, 1000.0f);

	mW = XMMatrixIdentity();
}

void GameObject::Init()
{
}

void GameObject::Update()
{
	Constant constTransform;
	
	XMMATRIX rotatY = XMMatrixRotationY(0);

	XMMATRIX rotatX = XMMatrixRotationX(XMConvertToRadians(0));

	XMMATRIX trans = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	mW = rotatX * rotatY * trans;

	constTransform.W = XMMatrixTranspose(mW);
	constTransform.V = XMMatrixTranspose(mV);
	constTransform.P = XMMatrixTranspose(mP);
	
	mCB.UpdateBufferResource(&constTransform, cDirect3D::GetContext());
}

void GameObject::Render()
{
	for (int i = 0; i < 1; i++)
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
