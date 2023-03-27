#include "SystemManager.h"
#include"GLFW/GLFWWindow.h"
#include"GUI/GuiWindowManager.h"
#include"Direct3D11/D3D11RenderingEngin.h"

namespace KALEIDOSCOPE
{ 
	namespace SYSTEM
	{
		SystemManager::SystemManager()
		{
		}
		SystemManager::~SystemManager()
		{
		}
		void SystemManager::SystemInitialize()
		{
			GLFW::GLFWWindow::InitGLFW(1920,1080,"KALEIDOSCOPE");
			GUI::GuiWindowManager::InitializeGuiWindowAll();
			RENDARINGENGIN::D3D11RenderingEngin::D3D11RenderingEnginInit();

		}
		void SystemManager::SystemRunning()
		{
			while (GLFW::GLFWWindow::ProcessMessage())
			{
				glfwPollEvents();
				//=======================================================================
				// 更新処理
				//=======================================================================
				GUI::GuiWindowManager::UpdateGuiWindowAll();



				//=======================================================================
				// 画面をクリア
				//=======================================================================
				RENDARINGENGIN::D3D11RenderingEngin::SetRenderTerget();
				GLFW::GLFWWindow::GLFWClear(0.6, 0.6, 0.6);

				//=======================================================================
				// 描画処理
				//=======================================================================
				GUI::GuiWindowManager::RenderGuiWindowAll();//最後に回したほうがいい


				//=======================================================================
				// バッファを交換
				//=======================================================================
				GLFW::GLFWWindow::GLFWSwapBuffers();
			}

		}
		void SystemManager::SystemShutDown()
		{
			GUI::GuiWindowManager::ShutDownGuiWindowAll();
			GLFW::GLFWWindow::ShutDownGLFW();
		}
	}

}


