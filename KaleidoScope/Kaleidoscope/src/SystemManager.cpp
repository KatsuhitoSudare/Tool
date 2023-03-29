#include "SystemManager.h"
#include"GLFW/GLFWWindow.h"
#include"GUI/GuiWindowManager.h"
#include"Direct3D11/D3D11RenderingEngin.h"
#include<chrono>
#include"Collection/Collection.h"
#include<string>
#include<fstream>
#include<sstream>

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
			//プロジェクトの初期化
			ProjectSettingFileInit();

			GLFW::GLFWWindow::InitGLFW(1920,1080,"KALEIDOSCOPE");
			GUI::GuiWindowManager::InitializeGuiWindowAll();
			RENDARINGENGIN::D3D11RenderingEngin::D3D11RenderingEnginInit();
		}
		void SystemManager::SystemRunning()
		{
			glfwSwapInterval(0);
			std::chrono::system_clock::time_point Now = std::chrono::system_clock::now(), End = std::chrono::system_clock::now();
			while (GLFW::GLFWWindow::ProcessMessage())
			{
				glfwPollEvents();

				Now = std::chrono::system_clock::now();
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
				End = std::chrono::system_clock::now();

				Time::DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(End - Now).count();
			}

		}
		void SystemManager::SystemShutDown()
		{
			GUI::GuiWindowManager::ShutDownGuiWindowAll();
			GLFW::GLFWWindow::ShutDownGLFW();
		}

		void SystemManager::ProjectSettingFileInit()
		{
			//シーンファイルの設定を取得
			std::ofstream ofs("ProjectSettings\\ProjectSetting.inf");
			if (!ofs)
			{
				//abot
			}



		}
	}

}


