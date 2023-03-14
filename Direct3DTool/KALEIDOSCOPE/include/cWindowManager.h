#pragma once
#include<Windows.h>
#ifdef _DEBUG
#pragma comment(lib,"Win32API_debug.lib")
#else
#pragma comment(lib,"Win32API.lib")
#endif // _DEBUG


class cWindowManager
{
public:
	static BOOL MakeWindow();
	static HWND GetWindowHandole();
	static void SetWindowSize(UINT width,UINT Height);
	static void SetWindowTitle(LPCWSTR );
	static BOOL ProcessMessage();

private:
	static inline HINSTANCE m_hInst;
	static inline HWND      m_hWnd;
	static inline UINT      m_WindowW;
	static inline UINT      m_WindowH;
	static inline LPCWSTR     m_WindowTitle;
	static inline LPCWSTR     m_WindowClass;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//コールバック関数
};

