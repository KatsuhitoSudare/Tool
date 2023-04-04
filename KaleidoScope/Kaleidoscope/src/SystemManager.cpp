#include "SystemManager.h"
#include"GLFW/GLFWWindow.h"
#include"GUI/GuiWindowManager.h"
#include"Direct3D11/D3D11RenderingEngin.h"
#include<chrono>
#include"Collection/Collection.h"
#include"SceneManager/SceneManager.h"
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
			ProjectSettingFileLoad();
			//シーンマネージャーの初期化
			SceneManager::SceneManagerInit(OpenScene.c_str());
			//GLFWの初期化
			GLFW::GLFWWindow::InitGLFW(1920,1080,"KALEIDOSCOPE");
			//GUIの初期化
			GUI::GuiWindowManager::InitializeGuiWindowAll();
			//レンダリングエンジンの初期化
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
				GLFW::GLFWWindow::GLFWClear(0.6f, 0.6f, 0.6f);

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
			SceneManager::SceneManagerShutDown();
			GLFW::GLFWWindow::ShutDownGLFW();
		}

		void SystemManager::ProjectSettingFileLoad()
		{
			//シーンファイルの設定を取得
			std::ifstream ifs("ProjectSettings/ProjectSetting.conf");
			std::string Buffer;

			while (std::getline(ifs, Buffer))
			{
				std::stringstream ss(Buffer);
				std::getline(ss, Buffer,' ');
				if (Buffer == "LastTimeOpenSceneFileDirectory")
				{
					std::getline(ss, Buffer,' ');
					OpenScene = Buffer;
				}
			}


		}
	}

}


