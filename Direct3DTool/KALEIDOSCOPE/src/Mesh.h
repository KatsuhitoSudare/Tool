#pragma once
#include<DirectXMath.h>
#include<d3d11.h>
#include<vector>

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







