#pragma once
#include<vector>
#include<map>
#include"GameObject.h"
#include"ModelLoader.h"

class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();

	virtual void SceneObjectInit() {};
	virtual void SceneObjectUpdate() {};
	virtual void SceneObjectRender() {};
	virtual void SceneObjectShutDown() {};

	template<class T>
	void CreateGameObject();

	void LoadModeldata(std::string modelname,std::string modelfilepath);

	ModelData GetModeldata(std::string modelname);

private:
	std::vector<GameObject*> m_GameObjectArray;
	std::map<std::string, ModelData> m_ModelArray;
};

template<class T>
inline void SceneObject::CreateGameObject()
{
	m_GameObjectArray.push_back(new T());
	m_GameObjectArray[m_GameObjectArray.size() - 1]->Init();
}
