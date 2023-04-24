#include "SceneObject.h"
#include<filesystem>
#include<string>
#include<fstream>
#include"..\picojson.h"

namespace KALEIDOSCOPE
{
	SceneObject::SceneObject()
	{
		GameObjectArray = new std::vector <KALEIDOSCOPE::COLLECTION::GameObject*>();
	}
	SceneObject::SceneObject(const char* SceneName)
	{
		GameObjectArray = new std::vector <KALEIDOSCOPE::COLLECTION::GameObject*>();
		this->SceneName = SceneName;

	}
	SceneObject::~SceneObject()
	{
		for (auto ite = GameObjectArray->begin(); ite != GameObjectArray->end(); ite++)
		{
			delete *ite;
		}
	}

	void SceneObject::OnInitGameObject()
	{
		std::ifstream ifs("SceneFile/" + SceneName + "/Settings.json");
		if (!ifs)
		{
			std::ofstream ofs("SceneFile/" + SceneName + "/Settings.json");
			if (ofs.is_open())
			{
				//jsonファイルのオブジェクト
				picojson::object jsonObj;

				//SceneCameraのポジションと注視点と上向きベクトル
				picojson::array Position { picojson::value(0.0f),picojson::value(0.0f),picojson::value(-1.0f)};
				picojson::array GazePoint{ picojson::value(0.0f),picojson::value(0.0f),picojson::value(0.0f) };
				picojson::array UpwardVec{ picojson::value(0.0f),picojson::value(1.0f),picojson::value(0.0f) };

				picojson::object CameraPosition;
				CameraPosition["Position"] = picojson::value(Position);
				CameraPosition["GazePoint"] = picojson::value(GazePoint);
				CameraPosition["UpwardVec"] = picojson::value(UpwardVec);

				
				jsonObj["SceneCameraPos"] = picojson::value(CameraPosition);

				//オブジェクトに書き込む
				ofs << picojson::value(jsonObj).serialize(true);
			}
		}
		
		for (const auto& entry : std::filesystem::directory_iterator("SceneFile/" + SceneName + "/object")) {
			if (!entry.is_directory())
			{
				//ゲームオブジェクトを作成
				KALEIDOSCOPE::COLLECTION::GameObject *pGameObject =  GameObjectArray->emplace_back(new KALEIDOSCOPE::COLLECTION::GameObject());

				//GameObjectの設置が書かれたファイルを開く
				std::ifstream ifs(entry.path());
				//Picojsonで読み込む
				picojson::value val;

				ifs >> val;

				pGameObject->ObjectName = val.get<picojson::object>()["Name"].get<std::string>();

				picojson::array transformval = val.get<picojson::object>()["Transform"].get<picojson::object>()["Position"].get<picojson::array>();


				pGameObject->transform.Pos.x = transformval[0].get<double>();
				pGameObject->transform.Pos.y = transformval[1].get<double>();
				pGameObject->transform.Pos.z = transformval[2].get<double>();

				transformval = val.get<picojson::object>()["Transform"].get<picojson::object>()["Scale"].get<picojson::array>();

				pGameObject->transform.Scale.x = transformval[0].get<double>();
				pGameObject->transform.Scale.y = transformval[1].get<double>();
				pGameObject->transform.Scale.z = transformval[2].get<double>();

				transformval = val.get<picojson::object>()["Transform"].get<picojson::object>()["Rotate"].get<picojson::array>();

				pGameObject->transform.Rotate.x = transformval[0].get<double>();
				pGameObject->transform.Rotate.y = transformval[1].get<double>();
				pGameObject->transform.Rotate.z = transformval[2].get<double>();

			}
		}
	}

	std::vector<KALEIDOSCOPE::COLLECTION::GameObject*>* SceneObject::GetGameObjectArray()
	{
		return GameObjectArray;
	}
	std::string SceneObject::GetSceneName()
	{
		return SceneName;
	}
}

