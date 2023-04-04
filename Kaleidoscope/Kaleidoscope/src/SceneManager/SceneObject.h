#pragma once
#include<vector>
#include"..\KaleidoScopeCollection\GameObject.h"

namespace KALEIDOSCOPE
{
	class SceneObject
	{
	public:
		SceneObject();
		SceneObject(const char* SceneName);
		~SceneObject();
		void OnInitGameObject(const char* ObjectDirectory);
		std::vector <KALEIDOSCOPE::COLLECTION::GameObject*>* GetGameObjectArray();

	private:
		//このシーンのオブジェクトを格納するコンテナ
		std::vector <KALEIDOSCOPE::COLLECTION::GameObject*> GameObjectArray;
		//このシーンの名前
		std::string SceneName;
	};
}



