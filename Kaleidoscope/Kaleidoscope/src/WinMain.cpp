#include<Windows.h>
#include"GLFW/GLFWWindow.h"
#include"GUI/GuiWindowManager.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GLFWWindow::InitGLFW(1280, 720, "title");
	KALEIDOSCOPE::GUI::GuiWindowManager::InitializeGuiWindowAll();

	while (GLFWWindow::ProcessMessage())
	{
		//イベントの処理
		glfwPollEvents();

		//GUIwindowの更新
		KALEIDOSCOPE::GUI::GuiWindowManager::UpdateGuiWindowAll();
		


		//画面のclear
		GLFWWindow::GLFWClear(0.6, 0.6, 0.6);
		KALEIDOSCOPE::GUI::GuiWindowManager::RenderGuiWindowAll();
		//バッファの切り替え
		GLFWWindow::GLFWSwapBuffers();
	}

	KALEIDOSCOPE::GUI::GuiWindowManager::ShutDownGuiWindowAll();
	//終了処理
	GLFWWindow::ShutDownGLFW();

	return 0;
}