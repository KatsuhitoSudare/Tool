#pragma once
#include"Direct3D11/ConstantBuffer.h"
#include"Direct3D11/IndexBuffer.h"
#include"Direct3D11/PixelShader.h"
#include"Direct3D11/VertexBuffer.h"
#include"Direct3D11/VertexShader.h"

//���_�̃f�[�^
struct Vertex
{
    DirectX::XMFLOAT3 Position; // �ʒu���W
    DirectX::XMFLOAT3 Normal;   // �@��
    DirectX::XMFLOAT2 UV;       // uv���W
    DirectX::XMFLOAT3 Tangent;  // �ڋ��
    DirectX::XMFLOAT4 Color;    // ���_�F
};

struct Mesh
{
    std::vector<Vertex> Vertices; // ���_�f�[�^�̔z��
    std::vector<uint32_t> Indices; // �C���f�b�N�X�̔z��
    const wchar_t* DiffuseMap; // �e�N�X�`���̃t�@�C���p�X
};


class GameObject
{
public:
	GameObject();

private:

};

