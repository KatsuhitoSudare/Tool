#include"SceneManager.h"
#include<filesystem>
#include<string>
#include<fstream>
#include"..\picojson.h"

namespace KALEIDOSCOPE
{
	void SceneManager::ChangeScene(const char* SceneName)
	{
		SceneManager Sm;
		Sm.SearchSceneDirectory("SceneFile", SceneName);
		IsChangeScene = true;
	}

	void SceneManager::SceneManagerInit(const char* SceneName)
	{
		if (!mpSceneObject)
		{
			mpSceneObject = new SceneObject(SceneName);
			mpSceneObject->OnInitGameObject();
		}
	}

	void SceneManager::SceneManagerShutDown()
	{
		if (mpSceneObject)
		{
			delete mpSceneObject;
		}
	}

	void SceneManager::SceneUpdate()
	{
		SceneManager Sm;
		if (IsChangeScene)
		{
			//シーンオブジェクトの破棄
			if (mpSceneObject)
			{
				delete mpSceneObject;
			}
			//新しく作る
			mpSceneObject = new SceneObject(NowOpenSceneFilePath.c_str());

			mpSceneObject->OnInitGameObject();
			//フラグを倒す
			IsChangeScene = false;
		}
	}

	void SceneManager::SceneRender()
	{
	}

	std::vector<GameObject*>* SceneManager::GetObjectArray()
	{
		return mpSceneObject->GetGameObjectArray();
	}

	GameObject* SceneManager::CreateGameObject()
	{
		return SceneManager::mpSceneObject->GetGameObjectArray()->emplace_back(new GameObject(SceneManager::CheckNameConflict("NewObject")));
	}

	string SceneManager::GetNowSceneName()
	{
		return mpSceneObject->GetSceneName();
	}

	std::string SceneManager::CheckNameConflict(std::string checkstring)
	{
		static int Version = 0;
		static std::string tempName = checkstring;

		for (auto obj : *mpSceneObject->GetGameObjectArray())
		{
			if (obj->ObjectName == checkstring)
			{
				Version++;
				return CheckNameConflict(tempName + std::to_string(Version));
			}
		}
		Version = 0;
		return checkstring;
	}

	bool SceneManager::SearchSceneDirectory(const char* DirectoryPath,const char* SceneName)
	{
		for (const auto& entry : std::filesystem::directory_iterator(DirectoryPath)) {
			if (entry.is_directory()) {
				if(entry.path().filename().string() == SceneName)
					NowOpenSceneFilePath = entry.path().string();
				break;
			}
			else
			{
				SearchSceneDirectory(entry.path().string().c_str(), SceneName);
			}
		}

		return true;
	}
}
