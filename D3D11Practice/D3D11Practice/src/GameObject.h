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
	virtual ~GameObject() {};
	virtual void Init();


	template<class T>
	T* GetComponent();

	template<class T>
	void AddComponent();

	std::string m_sModelName;

private:
	bool m_IsDestry;
	std::vector<Component*> m_ComponentArray;
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
	m_ComponentArray[m_ComponentArray.size() - 1]->Init();
}
