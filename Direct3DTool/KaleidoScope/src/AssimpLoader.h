#pragma once


#define NOMINMAX
#include <d3d12.h>
#include <DirectXMath.h>
#include <string>
#include <vector>

struct Mesh;
struct Vertex;

struct aiMesh;
struct aiMaterial;

struct ImportSettings // インポートするときのパラメータ
{
    const wchar_t* filename = nullptr; // ファイルパス
    std::vector<Mesh>& meshes; // 出力先のメッシュ
    bool inverseU = false; // U座標を反転させるか
    bool inverseV = false; // V座標を反転させるか
};

class AssimpLoader
{
public:
     static bool Load(ImportSettings setting); // モデルをロードする

private:
    static void LoadMesh(Mesh& dst, const aiMesh* src, bool inverseU, bool inverseV);
    //void LoadTexture(const wchar_t* filename, Mesh& dst, const aiMaterial* src);
};

