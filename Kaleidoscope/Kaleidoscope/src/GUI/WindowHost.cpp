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
            // ���j���[�o�[���쐬
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("New")) {
                        // �V�K�A�N�V�����̏���
                    }
                    if (ImGui::MenuItem("Open")) {
                        // �J���A�N�V�����̏���
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }


        }
    }
}


