#include "ModelLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifdef _DEBUG

#pragma comment(lib,"assimp-vc142-mtd.lib")

#else

#pragma comment(lib,"assimp-vc142-mt.lib")

#endif // _DEBUG


std::map<std::string, Mesh>  ModelLoader::LoadModel(const char* FilePath)
{
    aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);

    int flag = 0;
    flag |= aiProcess_Triangulate;
    //flag |= aiProcess_PreTransformVertices;
    flag |= aiProcess_CalcTangentSpace;
    //flag |= aiProcess_GenSmoothNormals;
    flag |= aiProcess_GenUVCoords;
    flag |= aiProcess_RemoveRedundantMaterials;
    flag |= aiProcess_OptimizeMeshes;
    flag |= aiProcess_MakeLeftHanded;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(FilePath, flag);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        return;
    }

    //メッシュの取得
    aiMesh* mesh = scene->mMeshes[0];

    std::map<std::string, Mesh> ModelMesh;

    //メッシュの情報を取得
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        //メッシュの名前を取得
        std::string MeshName = mesh[i].mName.C_Str();

        //頂点情報の取得
        for (int v = 0; v < mesh[i].mNumVertices; v++)
        {
            auto& Pos       = mesh[i].mVertices[v];
            auto& Normals   = mesh[i].mNormals[v];
            auto& UV        = mesh[i].mTextureCoords[0][v];
            auto& Tangent   = mesh[i].mTangents[v];
            auto& color     = mesh[i].mColors[0][v];

            Vertex Vert;
            Vert.Position = DirectX::XMFLOAT3(Pos.x,Pos.y,Pos.z);
            Vert.Normal = DirectX::XMFLOAT3(Normals.x, Normals.y, Normals.z);
            Vert.UV = DirectX::XMFLOAT2(UV.x,UV.y);
            Vert.Tangent = DirectX::XMFLOAT3(Tangent.x, Tangent.y, Tangent.z);
            Vert.Color = DirectX::XMFLOAT4(color.r, color.g, color.b, color.a);

            ModelMesh[MeshName].Vertices.push_back(Vert);
        }
    }

	return ModelMesh;
}
