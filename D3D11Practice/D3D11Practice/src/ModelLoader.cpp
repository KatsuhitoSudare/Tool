#include "ModelLoader.h"

#ifdef _DEBUG
#pragma comment(lib,"assimp-vc142-mtd.lib")
#endif // _DEBUG

#include "ModelLoader.h"

bool LoadModel(std::string const& FilePath, ModelData& dstData)
{
    //�C���|�[�^�[
    Assimp::Importer importer;

    //�ǂݍ��݃t���O
    int flag = 0;
    flag |= aiProcess_GenUVCoords;//UV���擾����t���O
    flag |= aiProcess_GenNormals;//�@�����擾����t���O
    flag |= aiProcess_MakeLeftHanded;

    //�V�[���f�[�^
    const aiScene* scene = importer.ReadFile(FilePath, flag);

    //�G���[����
    if (!scene)
    {
        std::string s = importer.GetErrorString();
        return false;
    }

    dstData.Meshes.resize(scene->mNumMeshes);

    for (int i = 0; i < dstData.Meshes.size(); i++)
    {
        //i�Ԗڂ�Mesh�̏��
        aiMesh* mesh = scene->mMeshes[i];
        dstData.Meshes[i].MeshName = mesh->mName.C_Str();
        //���_�����擾����
        for (int v = 0; v < mesh->mNumVertices; v++)
        {
            Vertex vertex;
            vertex.position = DirectX::XMFLOAT3(-mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
            vertex.normal = DirectX::XMFLOAT3(-mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
            vertex.texCoords = mesh->HasTextureCoords(0) ? DirectX::XMFLOAT2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y) : DirectX::XMFLOAT2(0.0f, 0.0f);
            dstData.Meshes[i].vertices.emplace_back(vertex);
        }
        
    }

    return true;
}
