#include<Windows.h>
#include"GLFW/GLFWWindow.h"
#include"GUI/WindowHost.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GLFWWindow::InitGLFW(1280, 720, "title");
	KALEIDOSCOPE::GUI::WindowHost::InitializeGUI();

	while (GLFWWindow::ProcessMessage())
	{
		//イベントの処理
		glfwPollEvents();

		KALEIDOSCOPE::GUI::WindowHost::UpdateGUI();
		
		
		//画面のclear
		GLFWWindow::GLFWClear(0.6, 0.6, 0.6);
		
		
		KALEIDOSCOPE::GUI::WindowHost::RenderGUI();


		//バッファの切り替え
		GLFWWindow::GLFWSwapBuffers();
	}

	KALEIDOSCOPE::GUI::WindowHost::ShutDownGUI();
	//終了処理
	GLFWWindow::ShutDownGLFW();

	return 0;
}