#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include<GLFW/glfw3.h>

const int WindowWidth = 640, WindowHeight = 480;
const char* AppTitle = "ClearScreen";

#ifdef UNICODE
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif // Win32
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, 0);
	auto window = glfwCreateWindow(WindowWidth, WindowHeight, AppTitle, nullptr, nullptr);

	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}