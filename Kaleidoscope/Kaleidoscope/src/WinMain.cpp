#include<Windows.h>
#include"GLFW/GLFWWindow.h"
#include"GUI/WindowHost.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GLFWWindow::InitGLFW(1280, 720, "title");
	KALEIDOSCOPE::GUI::WindowHost::InitializeGUI();

	while (GLFWWindow::ProcessMessage())
	{
		//�C�x���g�̏���
		glfwPollEvents();

		KALEIDOSCOPE::GUI::WindowHost::UpdateGUI();
		
		
		//��ʂ�clear
		GLFWWindow::GLFWClear(0.6, 0.6, 0.6);
		
		
		KALEIDOSCOPE::GUI::WindowHost::RenderGUI();


		//�o�b�t�@�̐؂�ւ�
		GLFWWindow::GLFWSwapBuffers();
	}

	KALEIDOSCOPE::GUI::WindowHost::ShutDownGUI();
	//�I������
	GLFWWindow::ShutDownGLFW();

	return 0;
}