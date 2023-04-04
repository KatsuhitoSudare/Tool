#include "WindowHost.h"
#include"..\IMGUI\imgui.h"
#include"..\IMGUI\imgui_impl_glfw.h"
#include"..\IMGUI\imgui_impl_opengl3.h"
#include"GLFW/glfw3.h"
#include"..\GLFW\GLFWWindow.h"
#include "../IMGUI/imgui_internal.h"
#include"..\SceneManager\SceneManager.h"
#include"..\picojson.h"
#include<fstream>

namespace KALEIDOSCOPE
{
    namespace GUI
    {
        WindowHost::WindowHost()
        {
            WindowName = "Host";
        }
        void WindowHost::Update()
        {
            // メニューバーを作成
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("New")) {
                        // 新規アクションの処理
                    }
                    if (ImGui::MenuItem("Open")) {
                        // 開くアクションの処理
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Edit"))
                {
                    if (ImGui::MenuItem("New")) {
                        // 新規アクションの処理
                    }
                    if (ImGui::MenuItem("Open")) {
                        // 開くアクションの処理
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("GameObject"))
                {
                    if (ImGui::MenuItem("Create")) {
                        SaveGameObject(SceneManager::CreateGameObject());
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMainMenuBar();
            }


        }

        void WindowHost::SaveGameObject(KALEIDOSCOPE::COLLECTION::GameObject* _SaveGameObject)
        {
            //Transformを書き込む
            picojson::array Position{picojson::value(_SaveGameObject->transform.Pos.x),picojson::value(_SaveGameObject->transform.Pos.y),picojson::value(_SaveGameObject->transform.Pos.z) };
            picojson::array Scale{ picojson::value(_SaveGameObject->transform.Scale.x),picojson::value(_SaveGameObject->transform.Scale.y),picojson::value(_SaveGameObject->transform.Scale.z) };
            picojson::array Rotate{ picojson::value(_SaveGameObject->transform.Rotate.x),picojson::value(_SaveGameObject->transform.Rotate.y),picojson::value(_SaveGameObject->transform.Rotate.z) };

            picojson::object transform;
            transform["Position"] = picojson::value(Position);
            transform["Scale"]    = picojson::value(Scale);
            transform["Rotate"]   = picojson::value(Rotate);

            picojson::object obj;
            obj["Name"] = picojson::value(_SaveGameObject->ObjectName.c_str());
            obj["Transform"] = picojson::value(transform);

            //ファイル名を作成する
            
            std::string SceneName = SceneManager::GetNowSceneName();
            std::string FileName = "SceneFile/" + SceneName + "/object/"+_SaveGameObject->ObjectName + ".json";

            std::ofstream ofs(FileName.c_str(), std::ios::trunc);
            if (!ofs)
            {
                ofs.open(FileName.c_str());
            }
            ofs << picojson::value(obj).serialize(true);
            ofs.close();
        }

        
    }
}


