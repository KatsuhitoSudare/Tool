#pragma once
#include<DirectXMath.h>
#include<vector>
#include<map>
#include<string>

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

class ModelLoader
{
public:
	static std::map<std::string,Mesh>  LoadModel(const char* FilePath);
};

