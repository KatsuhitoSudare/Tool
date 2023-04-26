#include "ModelLoader.h"

#ifdef _DEBUG
#pragma comment(lib,"assimp-vc142-mtd.lib")
#endif // _DEBUG

#include "ModelLoader.h"

DirectX::XMMATRIX aiToDxMatrix(const aiMatrix4x4& matrix)
{
    return DirectX::XMMATRIX(
        matrix.a1, matrix.a2, matrix.a3, matrix.a4,
        matrix.b1, matrix.b2, matrix.b3, matrix.b4,
        matrix.c1, matrix.c2, matrix.c3, matrix.c4,
        matrix.d1, matrix.d2, matrix.d3, matrix.d4);
}

bool ModelLoader::LoadModel(std::string const& FilePath,ModelData& dstData)
{
    //インポーター
    Assimp::Importer importer;

    //読み込みフラグ
    int flag = 0;
    flag |= aiProcess_GenUVCoords;//UVを取得するフラグ
    flag |= aiProcess_GenNormals;//法線を取得するフラグ
    flag |= aiProcess_MakeLeftHanded;

    //シーンデータ
    const aiScene* scene = importer.ReadFile(FilePath, flag);

    //エラー処理
    if (!scene)
    {
        std::string s = importer.GetErrorString();
        return false;
    }

    //メッシュの取得
    dstData.Meshes.resize(scene->mNumMeshes);
    for (int i = 0; i < dstData.Meshes.size(); i++)
    {
        //i番目のMeshの情報
        aiMesh* mesh = scene->mMeshes[i];
        dstData.Meshes[i].MeshName = mesh->mName.C_Str();
        //頂点情報を取得する
        for (int v = 0; v < mesh->mNumVertices; v++)
        {
            Vertex vertex;
            vertex.position = DirectX::XMFLOAT3(-mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
            vertex.normal = DirectX::XMFLOAT3(-mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
            vertex.texCoords = mesh->HasTextureCoords(0) ? DirectX::XMFLOAT2(mesh->mTextureCoords[0][v].x,mesh->mTextureCoords[0][v].y):DirectX::XMFLOAT2(0.0f,0.0f);
            for (int j = 0; j < 4; ++j)
            {
                vertex.boneIndices[j] = -1;
                vertex.boneWeights[j] = 0.0f;
            }
            dstData.Meshes[i].vertices.emplace_back(vertex);
        }

        if (mesh->HasBones())
        {
            //親子関係を構築
            for (int b = 0; b < mesh->mNumBones; b++)
            {
                //b番目のボーン
                aiBone* bone = mesh->mBones[b];
                dstData.Meshes[i].Bones[bone->mName.C_Str()].offsetMatrix *= aiToDxMatrix(bone->mOffsetMatrix);
                dstData.Meshes[i].Bones[bone->mName.C_Str()].BoneMatrix = DirectX::XMMatrixIdentity();
                aiNode* bone_node = scene->mRootNode->FindNode(bone->mName);

                for (int c = 0;c < bone_node->mNumChildren;c++)
                {
                    dstData.Meshes[i].Bones[bone->mName.C_Str()].ChildBoneName.push_back(bone_node->mChildren[c]->mName.C_Str());
                }

                for (int j = 0; j < bone->mNumWeights; j++)
                {
                    for (int k = 0; k < 4; ++k)
                    {
                        if (dstData.Meshes[i].vertices[bone->mWeights[j].mVertexId].boneWeights[k] == 0.0f)
                        {
                            dstData.Meshes[i].vertices[bone->mWeights[j].mVertexId].boneIndices[k] = b;
                            dstData.Meshes[i].vertices[bone->mWeights[j].mVertexId].boneWeights[k] = bone->mWeights[j].mWeight;
                            break;
                        }
                    }
                }
            }


        }
    }




    return true;
}

