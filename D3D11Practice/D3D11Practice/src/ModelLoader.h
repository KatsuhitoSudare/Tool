#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <DirectXMath.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Bone
{
    DirectX::XMFLOAT4X4 offsetMatrix;
    std::string         BoneName;
    Bone*               parentId;
};


struct Animation
{
    std::string name;
    double duration;
    double ticksPerSecond;
    std::vector<std::vector<DirectX::XMFLOAT4X4>> boneTransforms;
};

struct Vertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 texCoords;
    int boneIndices[4];  //頂点に影響を与えるボーンのインデックス
    float boneWeights[4];//頂点に影響を与えるボーンのウェイト
};

struct Mesh
{
    std::vector<Vertex>                        vertices;
    std::vector<unsigned int>                  indices;
    std::vector<Bone>                          Bones;
    // テクスチャ情報等を含める場合は、ここに追加
};

struct ModelData
{
    //モデルのメッシュ
    std::unordered_map<std::string, Mesh>      Meshes;
    //アニメーションデータ
    std::unordered_map<std::string, Animation> Animations;
};


class ModelLoader
{
public:
    static ModelData* LoadModel(const std::string const& FilePath);
private:
    static void LoadMesh(aiMesh& const _mesh, Mesh& dstMesh);
};

