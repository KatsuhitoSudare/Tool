#include "WindowHost.h"
#include"..\IMGUI\imgui.h"
#include"..\IMGUI\imgui_impl_glfw.h"
#include"..\IMGUI\imgui_impl_opengl3.h"
#include"GLFW/glfw3.h"
#include"..\GLFW\GLFWWindow.h"


namespace KALEIDOSCOPE
{
    namespace GUI
    {
        void WindowHost::InitializeGUI()
        {
            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
            //io.ConfigViewportsNoAutoMerge = true;
            //io.ConfigViewportsNoTaskBarIcon = true;

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();

            // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
            ImGuiStyle& style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }
            const char* glsl_version = "#version 130";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(GLFWWindow::GetContext(), true);
            ImGui_ImplOpenGL3_Init(glsl_version);
        }

        void WindowHost::UpdateGUI()
        {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            auto viewport = ImGui::GetMainViewport();

            ImGui::SetNextWindowPos(viewport->Pos);

            ImGui::SetNextWindowSize(viewport->Size);

            ImGui::SetNextWindowViewport(viewport->ID);

            ImGui::Begin("Hello, world!",NULL, ImGuiWindowFlags_NoResize| ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_MenuBar);                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

            ImGui::End();

        }

        void WindowHost::RenderGUI()
        {   
            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            int display_w, display_h;
            glfwGetFramebufferSize(GLFWWindow::GetContext(), &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);

            // Update and Render additional Platform Windows
            // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
            //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
        }

        void WindowHost::ShutDownGUI()
        {
            // Cleanup
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }
}


