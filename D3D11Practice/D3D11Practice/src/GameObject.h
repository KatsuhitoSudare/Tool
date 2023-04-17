#pragma once
#include"Direct3D11/ConstantBuffer.h"
#include"Direct3D11/IndexBuffer.h"
#include"Direct3D11/PixelShader.h"
#include"Direct3D11/VertexBuffer.h"
#include"Direct3D11/VertexShader.h"
#include"ModelLoader.h"

struct Constant
{
	XMMATRIX W;
	XMMATRIX V;
	XMMATRIX P;
};


class GameObject
{
public:
	GameObject();

private:
	VertexBuffer<Vertex> mVB;
	VertexShader         mVS;
	ConstantBuffer<Constant> mCB;
	IndexBuffer              mIB;
	PixelShader              mPS;
	std::vector<Mesh> Meshes;
};

