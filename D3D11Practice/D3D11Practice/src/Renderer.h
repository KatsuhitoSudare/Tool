#pragma once
#include "Component.h"
#include"Direct3D11/ConstantBuffer.h"
#include<DirectXMath.h>
#include"ModelLoader.h"

using namespace DirectX;

struct Constant
{
	XMMATRIX W;
	XMMATRIX V;
	XMMATRIX P;
};



class Renderer :public Component
{
public:
	virtual void Init(ModelData* data);
	virtual void Render();

private:

	std::vector<ConstantBuffer<Constant>> m_CB;
};

