#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <DirectXMath.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


struct Animation
{
    std::string name;
    double duration;
    double ticksPerSecond;
    std::vector<std::vector<DirectX::XMFLOAT4X4>> boneTransforms;
};

struct Bone
{
    DirectX::XMMATRIX   offsetMatrix;
    DirectX::XMMATRIX   BoneMatrix;
    Bone*               parentId;
    DirectX::XMFLOAT3   point;
};

struct Vertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT2 texCoords;
    DirectX::XMFLOAT3 normal;
    int   boneIndices[4];  //���_�ɉe����^����{�[���̃C���f�b�N�X
    float boneWeights[4];//���_�ɉe����^����{�[���̃E�F�C�g
};

struct Mesh
{
    std::string                                MeshName;
    std::vector<Vertex>                        vertices;
    std::vector<unsigned int>                  indices;
    std::unordered_map<std::string,Bone>       Bones;

    // �e�N�X�`����񓙂��܂߂�ꍇ�́A�����ɒǉ�
};

struct ModelData
{
    //���f���̃��b�V��
    std::vector<Mesh>                          Meshes;
    //�A�j���[�V�����f�[�^
    std::unordered_map<std::string, Animation> Animations;
};


class ModelLoader
{
public:
    static bool LoadModel(std::string const& FilePath, ModelData& dstData);
};

