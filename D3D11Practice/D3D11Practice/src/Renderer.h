#pragma once
#include "Component.h"
#include"Direct3D11/VertexBuffer.h"
#include"Direct3D11/ConstantBuffer.h"
#include"ResourceManager.h"
#include<DirectXMath.h>

using namespace DirectX;

struct Constant
{
	XMMATRIX W;
	XMMATRIX V;
	XMMATRIX P;
};

struct Material
{
	XMFLOAT4 BaceColor;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
};

struct DirectionalLite
{
	DirectX::XMFLOAT3 LiteVec;
	DirectX::XMFLOAT3 LiteColor;
	DirectX::XMFLOAT3 Eyepos;
};

class Renderer :public Component
{
public:
	using Component::Component;
	void Init()override;
	virtual void Render();
protected:
	Material m_material;
	std::vector<VertexBuffer<Vertex>> m_Vertex;
	ConstantBuffer<Material> m_cbMaterial;
	ConstantBuffer<Constant> m_cbWVP;
	ConstantBuffer<DirectionalLite> m_cbDirLite;
};

