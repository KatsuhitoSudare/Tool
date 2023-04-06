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

struct ImportSettings // �C���|�[�g����Ƃ��̃p�����[�^
{
    const wchar_t* filename = nullptr; // �t�@�C���p�X
    std::vector<Mesh>& meshes; // �o�͐�̃��b�V��
    bool inverseU = false; // U���W�𔽓]�����邩
    bool inverseV = false; // V���W�𔽓]�����邩
};

class AssimpLoader
{
public:
     static bool Load(ImportSettings setting); // ���f�������[�h����

private:
    static void LoadMesh(Mesh& dst, const aiMesh* src, bool inverseU, bool inverseV);
    //void LoadTexture(const wchar_t* filename, Mesh& dst, const aiMaterial* src);
};

