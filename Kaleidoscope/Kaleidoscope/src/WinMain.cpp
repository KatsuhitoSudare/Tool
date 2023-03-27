#include<Windows.h>
#include"GLFW/GLFWWindow.h"
#include"GUI/GuiWindowManager.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GLFWWindow::InitGLFW(1280, 720, "title");
	KALEIDOSCOPE::GUI::GuiWindowManager::InitializeGuiWindowAll();

	while (GLFWWindow::ProcessMessage())
	{
		//�C�x���g�̏���
		glfwPollEvents();

		//GUIwindow�̍X�V
		KALEIDOSCOPE::GUI::GuiWindowManager::UpdateGuiWindowAll();
		


		//��ʂ�clear
		GLFWWindow::GLFWClear(0.6, 0.6, 0.6);
		KALEIDOSCOPE::GUI::GuiWindowManager::RenderGuiWindowAll();
		//�o�b�t�@�̐؂�ւ�
		GLFWWindow::GLFWSwapBuffers();
	}

	KALEIDOSCOPE::GUI::GuiWindowManager::ShutDownGuiWindowAll();
	//�I������
	GLFWWindow::ShutDownGLFW();

	return 0;
}