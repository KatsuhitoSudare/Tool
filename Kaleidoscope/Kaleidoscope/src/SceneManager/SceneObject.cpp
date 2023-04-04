#include "SceneObject.h"
#include<filesystem>
#include<string>
#include<fstream>
#include"..\picojson.h"

namespace KALEIDOSCOPE
{
	SceneObject::SceneObject()
	{
	}
	SceneObject::SceneObject(const char* SceneName)
	{
		this->SceneName = SceneName;
	}
	SceneObject::~SceneObject()
	{
		for (auto ite = GameObjectArray.begin(); ite != GameObjectArray.end(); ite++)
		{
			delete *ite;
		}
	}

	void SceneObject::OnInitGameObject(const char* ObjectDirectory)
	{

	}

	std::vector<KALEIDOSCOPE::COLLECTION::GameObject*>* SceneObject::GetGameObjectArray()
	{
		return &GameObjectArray;
	}
}

