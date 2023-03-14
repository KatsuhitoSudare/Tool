#include "GameObject.h"
#include"cDirect3D.h"

#ifdef _DEBUG
#pragma comment(lib,"Direct3D11_debug.lib")
#else
#pragma comment(lib,"Direct3D11.lib")
#endif // _DEBUG

std::vector<Mesh> Meshes;

const wchar_t* modelFile = L"assets/Dragon 2.5_fbx.fbx";

//���_�̏��
D3D11_INPUT_ELEMENT_DESC desc[5] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��POSITION
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��NORMAL
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2��TEXCOORD
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��TANGENT
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4��COLOR
};

void GameObject::Init()
{
	ImportSettings importSetting = // ���ꎩ�͎̂���̓ǂݍ��ݐݒ�\����
	{
		modelFile,
		Meshes,
		false,
		true
	};

	//���_�V�F�[�_�[�̍쐬
	VS.InitVertexShader(L"Shader/VertexShader.hlsl", "vert", cDirect3D::GetDevice(), desc, 5);
	//�s�N�Z���V�F�[�_�[�̍쐬
	PS.InitPixelShader(L"Shader/PixelShader.hlsl", "pixel", cDirect3D::GetDevice());

	AssimpLoader::Load(importSetting);


	//���_�o�b�t�@�̍쐬
	VB.resize(Meshes.size());
	//���b�V���̐��������_�o�b�t�@���쐬����
	for (int i = 0; i < Meshes.size(); i++)
	{
		VB[i].CreateVertexBuffer(cDirect3D::GetDevice(),cDirect3D::GetContext(), Meshes[i].Vertices);
	}

	//�C���f�b�N�X�o�b�t�@�̍쐬
	IB.resize(Meshes.size());
	for (int i = 0; i < Meshes.size(); i++)
	{
		IB[i].CreateIndexBuffer(cDirect3D::GetDevice(), Meshes[i].Indices);
	}

	//�萔�o�b�t�@�̍쐬
	CB.CreateConstantBuffer(cDirect3D::GetDevice());
	
	XMVECTOR m_CameraPos = XMVectorSet(0.0f, 0.0f, -120-.0f, 0.0f);
	XMVECTOR m_Camerafocus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR m_CameraTop = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//�r���[���W��������
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
