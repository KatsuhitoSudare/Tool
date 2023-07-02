#pragma once
#include"SceneObject.h"
#include<memory>

class SceneManager
{
public:
	static void Init();
	static void ProcessSceneObject();
	static void ShutDouwn();

	template<class T>
	static void ChangeScene();
private:
	static inline bool IsChange = false;
	static inline std::unique_ptr<SceneObject> m_SceneObject;
	static inline SceneObject* m_tempSceneObject;

};

template<class T>
inline void SceneManager::ChangeScene()
{
	m_tempSceneObject = new T();
	IsChange = true;
}
