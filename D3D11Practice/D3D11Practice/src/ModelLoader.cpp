#include "ModelLoader.h"

#ifdef _DEBUG

#pragma comment(lib,"assimp-vc142-mtd.lib")

#else

#pragma comment(lib,"assimp-vc142-mt.lib")

#endif // _DEBUG

#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

bool ModelLoader::LoadModel(const std::string& path)
{
    Assimp::Importer importer;

    int flag = 0;
    flag |= aiProcess_Triangulate;
    //flag |= aiProcess_PreTransformVertices;
    flag |= aiProcess_CalcTangentSpace;
    //flag |= aiProcess_GenSmoothNormals;
    flag |= aiProcess_GenUVCoords;
    flag |= aiProcess_RemoveRedundantMaterials;
    flag |= aiProcess_OptimizeMeshes;
    flag |= aiProcess_MakeLeftHanded;

    const aiScene* scene = importer.ReadFile("unitychan.fbx", flag);

    if (!scene)
    {
        return false;
    }

    ProcessNode(scene->mRootNode, scene);

    return true;
}

bool ModelLoader::LoadAnimation(const std::string& path, const std::string& animationName)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return false;
    }

    if (scene->mNumAnimations == 0)
    {
        return false;
    }

    aiAnimation* aiAnim = scene->mAnimations[0];
    Animation animation;
    animation.name = animationName;
    animation.duration = aiAnim->mDuration;
    animation.ticksPerSecond = aiAnim->mTicksPerSecond != 0.0 ? aiAnim->mTicksPerSecond : 25.0;
    animation.boneTransforms.resize(aiAnim->mNumChannels, std::vector<DirectX::XMFLOAT4X4>(aiAnim->mDuration));

    for (unsigned int i = 0; i < aiAnim->mNumChannels; ++i)
    {
        aiNodeAnim* channel = aiAnim->mChannels[i];
        std::string nodeName(channel->mNodeName.data);
        auto boneIter = m_boneMapping.find(nodeName);

        if (boneIter != m_boneMapping.end())
        {
            unsigned int boneIndex = boneIter->second;

            for (unsigned int j = 0; j < channel->mNumPositionKeys; ++j)
            {
                aiVector3D position = channel->mPositionKeys[j].mValue;
                aiQuaternion rotation = channel->mRotationKeys[j].mValue;
                aiVector3D scaling = channel->mScalingKeys[j].mValue;

                aiMatrix4x4 matTranslation = aiMatrix4x4();
                aiMatrix4x4::Translation(position, matTranslation);

                aiMatrix4x4 matRotation = aiMatrix4x4(rotation.GetMatrix());

                aiMatrix4x4 matScaling = aiMatrix4x4();
                aiMatrix4x4::Scaling(scaling, matScaling);

                aiMatrix4x4 transform = matTranslation * matRotation * matScaling;
                DirectX::XMFLOAT4X4 dxTransform;
                memcpy(&dxTransform, &transform, sizeof(dxTransform));

                animation.boneTransforms[boneIndex][j] = dxTransform;
            }
        }
    }

    m_animations.push_back(animation);

    return true;
}

void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

ModelLoader::Mesh ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        vertex.position = DirectX::XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = DirectX::XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        vertex.texCoords = mesh->HasTextureCoords(0) ?
            DirectX::XMFLOAT2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) :
            DirectX::XMFLOAT2(0.0f, 0.0f);

        for (int j = 0; j < 4; ++j)
        {
            vertex.boneIndices[j] = -1;
            vertex.boneWeights[j] = 0.0f;
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // 骨のインデックスとウェイトを設定
    for (unsigned int i = 0; i < mesh->mNumBones; ++i)
    {
        aiBone* bone = mesh->mBones[i];

        for (unsigned int j = 0; j < bone->mNumWeights; ++j)
        {
            aiVertexWeight& weight = bone->mWeights[j];
            unsigned int vertexId = weight.mVertexId;
            float boneWeight = weight.mWeight;

            // 最初の空いているウェイトスロットに骨のインデックスとウェイトを追加
            for (int k = 0; k < 4; ++k)
            {
                if (vertices[vertexId].boneWeights[k] == 0.0f)
                {
                    vertices[vertexId].boneIndices[k] = i;
                    vertices[vertexId].boneWeights[k] = boneWeight;
                    break;
                }
            }
        }
    }

    return Mesh(vertices, indices);
}

void ModelLoader::ReadNodeHierarchy(float animationTime, const aiNode* pNode, const DirectX::XMFLOAT4X4& parentTransform, const Animation& animation)
{
}

const std::vector<ModelLoader::Mesh>& ModelLoader::GetMeshes() const
{
    return m_meshes;
}

const std::vector<Animation>& ModelLoader::GetAnimations() const
{
    return m_animations;
}

