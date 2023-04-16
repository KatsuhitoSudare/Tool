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

class ModelLoader
{
public:
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
        Mesh(std::vector<Vertex> v, std::vector<unsigned int> i)
        {
            vertices = v;
            indices = i;
        }
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        // テクスチャ情報等を含める場合は、ここに追加
    };

    ModelLoader();
    ~ModelLoader();

    bool LoadModel(const std::string& path);
    bool LoadAnimation(const std::string& path, const std::string& animationName);
    const std::vector<Mesh>& GetMeshes() const;
    const std::vector<Animation>& GetAnimations() const;

private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    void ReadNodeHierarchy(float animationTime, const aiNode* pNode, const DirectX::XMFLOAT4X4& parentTransform, const Animation& animation);

    std::vector<Mesh> m_meshes;
    std::vector<Animation> m_animations;
    std::unordered_map<std::string, unsigned int> m_boneMapping;
    std::vector<Bone> m_boneInfo;

};

