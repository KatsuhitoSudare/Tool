#include "ViewManager.h"
#include"cDirect3D.h"
#include"cWindowManager.h"
#include"IMGUI/imgui_impl_win32.h"
#include"IMGUI/imgui_impl_dx11.h"
#include"IMGUI/imgui.h"



namespace KALEIDOSCOPE
{
	namespace GUI
	{
		void ViewManager::Inititalize()
		{
			AssetsView = "AssetsView";
			SceneView  = "SceneView";
			GameView   = "GameView";
			HierarchyView = "HierarchyView";
			InspectorView = "InspectorView";
			MasterWindow  = "MasterWindow";

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            auto& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
            //io.ConfigViewportsNoAutoMerge = true;
            //io.ConfigViewportsNoTaskBarIcon = true;
            //io.ConfigViewportsNoDefaultParent = true;
            //io.ConfigDockingAlwaysTabBar = true;
            //io.ConfigDockingTransparentPayload = true;
            //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
            //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

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

            // Setup Platform/Renderer backends
            ImGui_ImplWin32_Init(cWindowManager::GetWindowHandole());
            ImGui_ImplDX11_Init(cDirect3D::GetDevice(), cDirect3D::GetContext());
			
		}
		void ViewManager::SutoDoun()
		{
            // Cleanup
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();
		}
		void ViewManager::Render()
		{
            // Start the Dear ImGui frame
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            //Ç±Ç±Ç…èàóùÇë}ì¸
            
            //=====================================================================
            // MasterViewÇï`âÊÇ∑ÇÈ
            //=====================================================================
            ImGuiWindowFlags windowflg = 0;
            windowflg |= ImGuiWindowFlags_NoTitleBar;
            windowflg |= ImGuiWindowFlags_NoMove;
            ImGui::SetNextWindowSize(ImVec2(winde, height));
            ImGui::Begin(MasterWindow.c_str(), 0, windowflg);           
            ImGui::End();
            //=====================================================================
            // MasterViewÇÃï`âÊèIóπ
            //=====================================================================




             // Rendering
            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            auto io = ImGui::GetIO();

            // Update and Render additional Platform Windows
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
            }

		}
        void ViewManager::SetMasterviewSize(float w, float h)
        {
            winde = w;
            height = h;
        }
	}
}
