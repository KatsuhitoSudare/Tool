#pragma once
#include<vector>
#include<map>
#include<utility>
#include"GameObject.h"
#include"ModelLoader.h"
#include"Direct3D11/VertexShader.h"
#include"Direct3D11/PixelShader.h"

class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();

	virtual void SceneObjectInit() {};
	void SceneObjectUpdate();
	void SceneObjectRender();
	void SceneObjectShutDown();


	template<class T>
	void CreateGameObject();

private:
	std::vector<GameObject*> m_GameObjectArray;
};

template<class T>
inline void SceneObject::CreateGameObject()
{
	m_GameObjectArray.push_back(new T());
	m_GameObjectArray[m_GameObjectArray.size() - 1]->Init();
}
