#pragma once
#include"Direct3D11/ConstantBuffer.h"
#include"Direct3D11/IndexBuffer.h"
#include"Direct3D11/PixelShader.h"
#include"Direct3D11/VertexBuffer.h"
#include"Direct3D11/VertexShader.h"
#include"ModelLoader.h"
#include"Component.h"

class GameObject
{
public:
	GameObject();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	template<class T>
	T* GetComponent();

	template<class T>
	void AddComponent();

private:
	std::vector<Component*> m_ComponentArray;

	std::vector<VertexBuffer<Vertex>>		mVB;
	VertexShader							mVS;
	ConstantBuffer<Constant>				mCB;
	std::vector<ConstantBuffer<BoneBuffer>> mBoneBuffer;
	IndexBuffer								mIB;
	PixelShader								mPS;
	ModelData								modelData;
};

template<class T>
inline T* GameObject::GetComponent()
{
	return nullptr;
}

template<class T>
inline void GameObject::AddComponent()
{
	m_ComponentArray.push_back(new T(this));
}
