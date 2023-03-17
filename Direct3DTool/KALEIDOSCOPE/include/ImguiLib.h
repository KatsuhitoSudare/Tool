#pragma once
#include<d3d11.h>
#include<map>
#include<string>
#include<vector>
#include<stdarg.h>

#define NoTitleBar 1
#define NoResize 2
#define NoMove 4

#pragma comment(lib,"ImguiLib.lib")

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

	void ImguiRender();

	void ImguiCreateButton(__in std::string WindowName, __in std::string ButtonName, __in void (*PushEvent)(), __in Kinds ButtonKinds);

	void ImguiCreateWindow(__in std::string WindowName);

	void ImguiCreateWindowEX(__in __in std::string WindowName, int WindowFlag);

	void ImguiCreateSliderF(__in std::string WindowName, __in std::string SliderName, __out float* SliderValue, __in float Min, __in float Max);

	void ImguiCreateText(const char* Text,...);

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

	struct SliderConfig
	{
		std::string SliderName;
		float* SliderValue;
		float Max;
		float Min;
	};

	struct ImguiWindowConfig
	{
		//�E�B���h�E�̖��O
		std::string WindowName;
		//�{�^��
		std::vector<ButtonConfig*> ButtonArray;
		//�X���C�_�[
		std::vector<SliderConfig*> SlliderArray;
		//Window�̕\�����
		bool DisplayState = true;
		//�E�B���h�E�̌�����
		int  flg;
	};


	ImguiLib() {};
	static ImguiLib* instatnce;
	
	std::map<std::string, ImguiWindowConfig*> WindowArray;
	HWND hWnd = NULL;
};

#define IMGUILIB ImguiLib::GetInstatnce()

