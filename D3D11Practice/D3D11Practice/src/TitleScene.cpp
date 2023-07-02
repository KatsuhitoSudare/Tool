#include "TitleScene.h"
#include "Player.h"
#include"ResourceManager.h"

void TitleScene::SceneObjectInit()
{
	ResourceManager::LoadVertexShader("SimpleVs", L"Shader/VS.hlsl");
	ResourceManager::LoadPixelShader("SimplePs", L"Shader/PS.hlsl");
	ResourceManager::LoadModelData("Player", "asset/walking.fbx");
	CreateGameObject<Player>();
}

