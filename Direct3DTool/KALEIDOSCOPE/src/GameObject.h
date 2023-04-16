#pragma once
#include"VertexBuffer.h"
#include"VertexShader.h"
#include"PixelShader.h"
#include"ConstantBuffer.h"
#include"IndexBuffer.h"
#include"Mesh.h"
#include<DirectXMath.h>
#include"AssimpLoader.h"

using namespace DirectX;

struct Constant
{
	XMMATRIX W;
	XMMATRIX V;
	XMMATRIX P;
};

class GameObject
{
public:
	GameObject() {};
	~GameObject() {};
	void Init();
	void Draw();
private:
	std::vector<VertexBuffer<Vertex>>	 VB;
	std::vector<IndexBuffer>			 IB;
	ConstantBuffer<Constant> CB;
	VertexShader             VS;
	PixelShader				 PS;

	XMMATRIX  mW;
	XMMATRIX  mV;
	XMMATRIX  mP;
};

