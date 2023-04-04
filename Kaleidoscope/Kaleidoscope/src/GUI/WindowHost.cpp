#include "WindowHost.h"
#include"..\IMGUI\imgui.h"
#include"..\IMGUI\imgui_impl_glfw.h"
#include"..\IMGUI\imgui_impl_opengl3.h"
#include"GLFW/glfw3.h"
#include"..\GLFW\GLFWWindow.h"
#include "../IMGUI/imgui_internal.h"
#include"..\SceneManager\SceneManager.h"

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
                        SceneManager::GetObjectArray()->push_back(new GameObject("object"));
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMainMenuBar();
            }


        }
    }
}


