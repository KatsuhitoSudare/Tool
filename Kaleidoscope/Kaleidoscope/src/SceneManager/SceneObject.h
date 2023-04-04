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
		void OnInitGameObject();
		std::vector <KALEIDOSCOPE::COLLECTION::GameObject*>* GetGameObjectArray();
		std::string GetSceneName();
	private:
		//���̃V�[���̃I�u�W�F�N�g���i�[����R���e�i
		std::vector <KALEIDOSCOPE::COLLECTION::GameObject*>* GameObjectArray;
		//���̃V�[���̖��O
		std::string SceneName;
	};
}



