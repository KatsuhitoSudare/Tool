#pragma once
#include<DirectXMath.h>
#include<d3d11.h>
#include<vector>

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







