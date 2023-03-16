#include "..\..\KALEIDOSCOPE\include\cWindowManager.h"
#include"..\..\KALEIDOSCOPE\include\ImguiLib.h"
#include <iostream>
#include <sstream>
#include <string>



BOOL cWindowManager::MakeWindow()
{
	m_hInst = GetModuleHandle(nullptr);
	if (!m_hInst)
	{
		return FALSE;
	}

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_WindowClass;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	m_hWnd = CreateWindowEx(0,                // 拡張ウィンドウスタイル
		m_WindowTitle,                        // ウィンドウクラスの名前
		m_WindowTitle,                        // ウィンドウの名前
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,    // ウィンドウスタイル
		CW_USEDEFAULT,						  // ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,						  // ウィンドウの左上Ｙ座標 
		m_WindowW,							  // ウィンドウの幅
		m_WindowH,							  // ウィンドウの高さ
		NULL,								  // 親ウィンドウのハンドル
		NULL,								  // メニューハンドルまたは子ウィンドウID
		m_hInst,							  // インスタンスハンドル
		NULL);								  // ウィンドウ作成データ

	if (!m_hWnd)
	{
		MessageBox(NULL, TEXT("ウィンドウの作成に失敗"),
			TEXT("結果"), MB_ICONINFORMATION);
		return FALSE;
	}

	/*RECT rcWnd, rcClient;
	GetWindowRect(m_hWnd, &rcWnd);
	GetClientRect(m_hWnd, &rcClient);
	m_WindowW = (rcWnd.right - rcWnd.left) - (rcClient.right - rcClient.left) + m_WindowW;
	m_WindowH = (rcWnd.bottom - rcWnd.top) - (rcClient.bottom - rcClient.top) + m_WindowH;
	SetWindowPos(m_hWnd, NULL, 0, 0, m_WindowW, m_WindowH, SWP_NOMOVE | SWP_NOZORDER);*/

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(m_hWnd);


	return 0;
}

HWND cWindowManager::GetWindowHandole()
{
	return m_hWnd;
}

void cWindowManager::SetWindowSize(UINT width, UINT Height)
{
	m_WindowW = width;
	m_WindowH = Height;
}

void cWindowManager::SetWindowTitle(LPCWSTR Title)
{
	m_WindowTitle = Title;
	m_WindowClass = Title;
}

BOOL cWindowManager::ProcessMessage()
{
	MSG msg = {};

	while (WM_QUIT != msg.message &&
		PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (WM_QUIT == msg.message)
	{
		return FALSE;
	}

	return TRUE;
}

LRESULT cWindowManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (IMGUILIB->ImGuiProc(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:
	{ PostQuitMessage(0); }
	break;

	case WM_KEYDOWN:
		if (LOWORD(wParam) == VK_ESCAPE)
		{
			// xボタンが押されたのと同じ効果を発揮する
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);
		}
		break;
	default:
	{ /* DO_NOTHING */ }
	break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
