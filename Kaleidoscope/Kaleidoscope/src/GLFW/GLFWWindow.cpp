#include "GLFWWindow.h"
#include<gl/GL.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glfw3dll.lib")
#pragma comment(lib,"glfw3_mt.lib")

int GLFWWindow::InitGLFW(int WindowW, int WindowH, const char* WindowTitle)
{
    //GLFWの初期化
	if (!glfwInit())
		return 0;

    //ウィンドウの作成
    window = glfwCreateWindow(WindowW, WindowH, WindowTitle, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }

    //現在のスレッドにOpenGLコンテキストを関連付けます
    glfwMakeContextCurrent(window);

    //最大サイズですたーとさせる
    glfwMaximizeWindow(window);

    //スワップチェインのインターバルを決める
    glfwSwapInterval(1);

    return 1;
}

void GLFWWindow::ShutDownGLFW()
{
    glfwTerminate();
}

void GLFWWindow::GLFWClear(float R, float G, float B)
{
    glClearColor(R, G, B, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLFWWindow::GLFWSwapBuffers()
{
    // ダブルバッファのスワップ
    glfwSwapBuffers(window);
}

bool GLFWWindow::ProcessMessage()
{
    return !glfwWindowShouldClose(window);
}

GLFWwindow* GLFWWindow::GetContext()
{
    return window;
}
