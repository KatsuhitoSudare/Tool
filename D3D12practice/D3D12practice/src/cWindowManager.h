#pragma once
#include<Windows.h>
#include<d3d11.h>


class cWindowManager
{
public:
	static BOOL MakeWindow();
	static HWND GetWindowHandole();
	static void GetWindowSize(UINT* w,UINT* h);
	static void SetWindowSize(UINT width,UINT Height);
	static void SetWindowTitle(LPCSTR );
	static BOOL ProcessMessage();
private:
	static inline HINSTANCE m_hInst;
	static inline HWND      m_hWnd;
	static inline UINT      m_WindowW;
	static inline UINT      m_WindowH;
	static inline LPCSTR     m_WindowTitle;
	static inline LPCSTR     m_WindowClass;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//コールバック関数
};

