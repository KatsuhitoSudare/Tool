#pragma once
#include"Direct3D11/ConstantBuffer.h"
#include"Direct3D11/IndexBuffer.h"
#include"Direct3D11/PixelShader.h"
#include"Direct3D11/VertexBuffer.h"
#include"Direct3D11/VertexShader.h"

//頂点のデータ
struct Vertex
{
    DirectX::XMFLOAT3 Position; // 位置座標
    DirectX::XMFLOAT3 Normal;   // 法線
    DirectX::XMFLOAT2 UV;       // uv座標
    DirectX::XMFLOAT3 Tangent;  // 接空間
    DirectX::XMFLOAT4 Color;    // 頂点色
};

struct Mesh
{
    std::vector<Vertex> Vertices; // 頂点データの配列
    std::vector<uint32_t> Indices; // インデックスの配列
    const wchar_t* DiffuseMap; // テクスチャのファイルパス
};


class GameObject
{
public:
	GameObject();

private:

};

