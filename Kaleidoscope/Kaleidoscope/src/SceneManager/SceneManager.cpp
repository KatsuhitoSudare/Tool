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
		Sm.SearchSceneFile("Assets", SceneName);
		IsChangeScene = true;
	}

	void SceneManager::SceneManagerInit(const char* SceneName)
	{
		ChangeScene(SceneName);
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
			//�V�[���I�u�W�F�N�g�̔j��
			if (mpSceneObject)
			{
				delete mpSceneObject;
			}
			//�V�������
			mpSceneObject = new SceneObject(NowOpenSceneFilePath.c_str());
			//�t���O��|��
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

	bool SceneManager::SearchSceneFile(const char* DirectoryPath,const char* SceneName)
	{
		for (const auto& entry : std::filesystem::directory_iterator(DirectoryPath)) {
			if (entry.is_directory()) {
				SearchSceneFile(entry.path().string().c_str(),SceneName);
			}
			else
			{
				if (entry.path().filename().string() == SceneName)
				{
					NowOpenSceneFilePath = entry.path().string();
					break;
				}
			}
		}

		return true;
	}
}
