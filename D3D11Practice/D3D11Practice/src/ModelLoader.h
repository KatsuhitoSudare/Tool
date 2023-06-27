#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <DirectXMath.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT2 texCoords;
    DirectX::XMFLOAT3 normal;
};

struct Mesh
{
    std::string                                MeshName;
    std::vector<Vertex>                        vertices;
    std::vector<unsigned int>                  indices;
};

struct ModelData
{
    //ƒ‚ƒfƒ‹‚ÌƒƒbƒVƒ…
    std::vector<Mesh>                          Meshes;
};

bool LoadModel(std::string const& FilePath, ModelData& dstData);

