#pragma once
#include"GLFW/glfw3.h"
#include"GLFW/glfw3native.h"

class GLFWWindow
{
public:
	static int  InitGLFW(int WindowW,int WindowH,const char* WindowTitle);
	static void ShutDownGLFW();
	static void GLFWClear(float R, float G, float B);
	static void GLFWSwapBuffers();
	static bool ProcessMessage();
	static GLFWwindow* GetContext();
private:
	static inline GLFWwindow* window;
};

