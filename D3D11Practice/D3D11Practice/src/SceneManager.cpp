#include "SceneManager.h"
#include"TitleScene.h"

void SceneManager::Init()
{
	ChangeScene<TitleScene>();
}

void SceneManager::ProcessSceneObject()
{
	m_SceneObject->SceneObjectUpdate();
	m_SceneObject->SceneObjectRender();
	if (IsChange)
	{
		m_SceneObject->SceneObjectShutDown();
		m_SceneObject.reset(m_tempSceneObject);
		m_SceneObject->SceneObjectInit();
		IsChange = false;
	}
}

void SceneManager::ShutDouwn()
{
	m_SceneObject->SceneObjectShutDown();
	m_SceneObject.release();
}
