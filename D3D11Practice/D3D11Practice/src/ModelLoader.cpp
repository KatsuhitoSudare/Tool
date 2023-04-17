#include "ModelLoader.h"

#ifdef _DEBUG
#pragma comment(lib,"assimp-vc142-mtd.lib")
#else
#pragma comment(lib,"assimp-vc142-mt.lib")
#endif // _DEBUG

#include "ModelLoader.h"

DirectX::XMFLOAT4X4 aiToDxMatrix(const aiMatrix4x4& matrix)
{
    return DirectX::XMFLOAT4X4(
        matrix.a1, matrix.a2, matrix.a3, matrix.a4,
        matrix.b1, matrix.b2, matrix.b3, matrix.b4,
        matrix.c1, matrix.c2, matrix.c3, matrix.c4,
        matrix.d1, matrix.d2, matrix.d3, matrix.d4);
}

ModelData* ModelLoader::LoadModel(const std::string const& FilePath)
{
    //インポーター
    Assimp::Importer importer;

    //読み込みフラグ
    int flag = 0;
    flag |= aiProcess_Triangulate;
    //flag |= aiProcess_PreTransformVertices;
    flag |= aiProcess_CalcTangentSpace;
    //flag |= aiProcess_GenSmoothNormals;
    flag |= aiProcess_GenUVCoords;
    flag |= aiProcess_RemoveRedundantMaterials;
    flag |= aiProcess_OptimizeMeshes;
    flag |= aiProcess_MakeLeftHanded;

    //シーンデータ
    const aiScene* scene = importer.ReadFile(FilePath, flag);

    //エラー処理
    if (!scene)
    {
        std::string s = importer.GetErrorString();
        return nullptr;
    }

    ModelData modelData;//return用のModelData


    //メッシュの取得
    aiMesh* aimesh = scene->mMeshes[0];
    for (int i = 0; i < scene->mNumMeshes; i++)
    {
        LoadMesh(aimesh[i],modelData.Meshes[aimesh[i].mName.C_Str()]);
    }

	return nullptr;
}

void ModelLoader::LoadMesh(aiMesh& const _mesh, Mesh& dstMesh)
{
    //頂点の情報の取得
    for (int i = 0; i < _mesh.mNumVertices; i++)
    {
        Vertex vertex;
        vertex.position = DirectX::XMFLOAT3(_mesh.mVertices[i].x, _mesh.mVertices[i].y, _mesh.mVertices[i].z);
        vertex.normal = DirectX::XMFLOAT3(_mesh.mNormals[i].x, _mesh.mNormals[i].y, _mesh.mNormals[i].z);
        vertex.texCoords = DirectX::XMFLOAT2(_mesh.mTextureCoords[0][i].x, _mesh.mTextureCoords[0][i].y);
        for (int j = 0; j < 4; ++j)
        {
            vertex.boneIndices[j] = -1;
            vertex.boneWeights[j] = 0.0f;
        }
        dstMesh.vertices.emplace_back(vertex);
    }
    
    //indexの取得
    for (unsigned int i = 0; i < _mesh.mNumFaces; i++)
    {
        aiFace face = _mesh.mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            dstMesh.indices.emplace_back(face.mIndices[j]);
        }
    }

    std::vector<Bone> bonearray;
    bonearray.resize(_mesh.mNumBones);
    for (int i = 0; i < _mesh.mNumBones; i++)
    {
        aiBone* bone  = _mesh.mBones[i];
        for (int j = 0; j < bone->mNumWeights; j++)
        {
            bonearray[i].BoneName = bone->mName.C_Str();
            bonearray[i].offsetMatrix = aiToDxMatrix(bone->mOffsetMatrix);
            for (int w = 0; w < bone->mNumWeights; w++)
            {
                for (int k = 0; k < 4; ++k)
                {
                    if (dstMesh.vertices[bone->mWeights->mVertexId].boneWeights[k] == 0.0f)
                    {
                        dstMesh.vertices[bone->mWeights->mVertexId].boneIndices[k] = i;
                        dstMesh.vertices[bone->mWeights->mVertexId].boneWeights[k] = bone->mWeights->mWeight;
                    }
                }

            }
        }
    }

    dstMesh.Bones = bonearray;
}
