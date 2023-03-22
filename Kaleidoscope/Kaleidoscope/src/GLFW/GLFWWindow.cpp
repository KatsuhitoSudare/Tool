#include "GLFWWindow.h"
#include<gl/GL.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glfw3dll.lib")
#pragma comment(lib,"glfw3_mt.lib")

int GLFWWindow::InitGLFW(int WindowW, int WindowH, const char* WindowTitle)
{
    //GLFW�̏�����
	if (!glfwInit())
		return 0;

    //�E�B���h�E�̍쐬
    window = glfwCreateWindow(WindowW, WindowH, WindowTitle, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }

    //���݂̃X���b�h��OpenGL�R���e�L�X�g���֘A�t���܂�
    glfwMakeContextCurrent(window);

    //�ő�T�C�Y�ł����[�Ƃ�����
    glfwMaximizeWindow(window);

    //�X���b�v�`�F�C���̃C���^�[�o�������߂�
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
    // �_�u���o�b�t�@�̃X���b�v
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
