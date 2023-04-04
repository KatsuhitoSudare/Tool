#pragma once
#include<string>
#include"..\KaleidoScopeCollection\GameObject.h"
#include"..\KaleidoScopeCollection\Camera.h"
#include"SceneObject.h"

using namespace KALEIDOSCOPE::COLLECTION;

namespace KALEIDOSCOPE
{
	class SceneManager
	{
	public:
		static void ChangeScene(const char* SceneName);
		static void SceneManagerInit(const char* SceneName);
		static void SceneManagerShutDown();
		static void SceneUpdate();
		static void SceneRender();
		static std::vector<GameObject*>* GetObjectArray();
	private:
		//=========================================================
		// fanction
		//=========================================================
		bool SearchSceneFile(const char* DirectoryPath, const char* SceneName);

		//=========================================================
		// variable
		//=========================================================
		static inline SceneObject* mpSceneObject;
		static inline std::string NowOpenSceneFilePath;
		static inline Camera* SceneCamera;
		static inline bool IsChangeScene = false;
	};

}

