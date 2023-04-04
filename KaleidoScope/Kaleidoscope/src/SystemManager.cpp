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
			//�v���W�F�N�g�̏�����
			ProjectSettingFileLoad();
			//�V�[���}�l�[�W���[�̏�����
			SceneManager::SceneManagerInit(OpenScene.c_str());
			//GLFW�̏�����
			GLFW::GLFWWindow::InitGLFW(1920,1080,"KALEIDOSCOPE");
			//GUI�̏�����
			GUI::GuiWindowManager::InitializeGuiWindowAll();
			//�����_�����O�G���W���̏�����
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
				// �X�V����
				//=======================================================================
				GUI::GuiWindowManager::UpdateGuiWindowAll();



				//=======================================================================
				// ��ʂ��N���A
				//=======================================================================
				RENDARINGENGIN::D3D11RenderingEngin::SetRenderTerget();
				GLFW::GLFWWindow::GLFWClear(0.6f, 0.6f, 0.6f);

				//=======================================================================
				// �`�揈��
				//=======================================================================
				GUI::GuiWindowManager::RenderGuiWindowAll();//�Ō�ɉ񂵂��ق�������


				//=======================================================================
				// �o�b�t�@������
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
			//�V�[���t�@�C���̐ݒ���擾
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


