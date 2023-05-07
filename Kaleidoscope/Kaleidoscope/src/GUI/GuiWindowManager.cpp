#include "GuiWindowManager.h"
#include"..\IMGUI\imgui.h"
#include"..\IMGUI\imgui_impl_glfw.h"
#include"..\IMGUI\imgui_impl_opengl3.h"
#include"..\GLFW\GLFWWindow.h"
#include"WindowHost.h"
#include"InspecterView.h"
#include"HierarchyView.h"
#include"GameView.h"
#include"ProjectView.h"
#include"SceneView.h"
#include"ConsoleView.h"
#include"Toolbar.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		
		void GuiWindowManager::InitializeGuiWindowAll()
		{
			//ImGuiを初期化する
			ImGuiInit();
			
			//Hostのwindowを追加
			WindowArray.emplace_back(new WindowHost());
			//InspecterViewを追加
			WindowArray.emplace_back(new InspecterView());
			//HierarchyViewの追加
			WindowArray.emplace_back(new HierarchyView());
			//AssetsViewの追加
			WindowArray.emplace_back(new ProjectView());
			//SceneViewの追加
			WindowArray.emplace_back(new SceneView());
			//GameViewの追加
			WindowArray.emplace_back(new GameView());
			//ConsoleViewの追加
			WindowArray.emplace_back(new ConsoleView());
			//Toolbarの追加
			WindowArray.emplace_back(new Toolbar());
		}
		void GuiWindowManager::UpdateGuiWindowAll()
		{
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// ここでドッキングスペースを設定する
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_None);

			for (auto window : WindowArray)
			{
				window->Update();
			}
		}
		void GuiWindowManager::RenderGuiWindowAll()
		{
			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			int display_w, display_h;
			glfwGetFramebufferSize(GLFW::GLFWWindow::GetContext(), &display_w, &display_h);
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
		void GuiWindowManager::ShutDownGuiWindowAll()
		{
			for (int i = 0; i < WindowArray.size(); i++)
			{
				delete WindowArray[i];
			}

			// Cleanup
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
		void* GuiWindowManager::GetSelectObject()
		{
			return SelectObject;
		}
		void GuiWindowManager::SetSelectObject(void* _select)
		{
			SelectObject = _select;
		}
		void GuiWindowManager::ImGuiInit()
		{
			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;			// Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;			// Enable Multi-Viewport / Platform Windows
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
			// Setup Platform/Renderer backends
			ImGui_ImplGlfw_InitForOpenGL(GLFW::GLFWWindow::GetContext(), true);
			ImGui_ImplOpenGL3_Init(glsl_version);
		}
	}
}


