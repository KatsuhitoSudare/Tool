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

struct BoneBuffer
{
	XMMATRIX bone[100];
};


class GameObject
{
public:
	GameObject();
	void Update();
	void Render();
private:
	std::vector<VertexBuffer<Vertex>>		mVB;
	VertexShader							mVS;
	ConstantBuffer<Constant>				mCB;
	std::vector<ConstantBuffer<BoneBuffer>> mBoneBuffer;
	IndexBuffer								mIB;
	PixelShader								mPS;
	ModelData								modelData;

	XMMATRIX								mW;
	XMMATRIX								mV;
	XMMATRIX								mP;
};

