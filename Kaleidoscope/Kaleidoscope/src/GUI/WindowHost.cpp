#include "WindowHost.h"
#include"..\IMGUI\imgui.h"
#include"..\IMGUI\imgui_impl_glfw.h"
#include"..\IMGUI\imgui_impl_opengl3.h"
#include"GLFW/glfw3.h"
#include"..\GLFW\GLFWWindow.h"
#include "../IMGUI/imgui_internal.h"


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
                ImGui::EndMainMenuBar();
            }


        }
    }
}


