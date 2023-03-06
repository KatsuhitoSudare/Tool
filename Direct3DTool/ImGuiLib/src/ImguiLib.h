#pragma once
#include<d3d11.h>
#include<map>
#include<string>
#include<vector>

enum Kinds
{
	Stay,
	Enter,
	Exit,
	Edge
};

class ImguiLib
{
public:
	static ImguiLib* GetInstatnce()
	{
		if (instatnce == nullptr)
		{
			instatnce = new ImguiLib();
		}

		return instatnce;
	};
	
	void Initialize(__in HWND _hWnd, __in ID3D11Device* const d3ddevice, __in ID3D11DeviceContext* const _d3dcontext);

	void Shutdown();

	void RenderImgui();

	void CreateButton(std::string WindowName, std::string ButtonName, void (*PushEvent)(), Kinds ButtonKinds);

	void ImguiCreateWindow(std::string WindowName);

	LRESULT ImGuiProc(HWND hWbd, UINT msg, WPARAM wParam, LPARAM lParam);

	~ImguiLib();
private:
	

	struct ButtonConfig
	{
		std::string ButtonName;
		void (*Event)();
		Kinds ButtonKinds;
		bool Edge;
	};

	struct ImguiWindowConfig
	{
		//ウィンドウの名前
		std::string WindowName;
		//ボタン
		std::vector<ButtonConfig*> ButtonArray;

	};


	ImguiLib() {};
	static ImguiLib* instatnce;
	std::map<std::string, ImguiWindowConfig*> WindowArray;
	HWND hWnd = NULL;
};

#define IMGUILIB ImguiLib::GetInstatnce()

