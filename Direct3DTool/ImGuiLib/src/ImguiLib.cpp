#include"ImguiLib.h"
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include<windowsx.h>

ImguiLib* ImguiLib::instatnce = nullptr;
// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


void ImguiLib::Initialize(__in HWND _hWnd,
	__in ID3D11Device* const d3ddevice,
	__in ID3D11DeviceContext* const _d3dcontext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(_hWnd);
	ImGui_ImplDX11_Init(d3ddevice, _d3dcontext);
	hWnd = _hWnd;
}

void ImguiLib::Shutdown()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImguiLib::ImguiRender()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto& Window : WindowArray)
	{
		ImGui::Begin(Window.first.c_str());

		//ボタンの処理
		{
			for (auto& button : Window.second->ButtonArray)
			{
				if (ImGui::Button(button->ButtonName.c_str()))
				{
					if (button->ButtonKinds == Edge)
					{
						if (button->Edge == false)
						{
							button->Event();
						}
					}
					else
					{
						button->Event();
					}

					button->Edge = true;
				}
				else
				{
					button->Edge = false;
				}
			}
		}

		//スライダーの処理
		{
			for (auto slider : Window.second->SlliderArray)
			{
				ImGui::SliderFloat(slider->SliderName.c_str(), slider->SliderValue, slider->Min, slider->Max);
			}
		}
		

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImguiLib::ImguiCreateButton(std::string WindowName, std::string ButtonName, void(*PushEvent)(), Kinds ButtonKinds)
{
	WindowArray[WindowName]->ButtonArray.emplace_back(new ButtonConfig());
	WindowArray[WindowName]->ButtonArray[WindowArray[WindowName]->ButtonArray.size() - 1]->ButtonName = ButtonName;
	WindowArray[WindowName]->ButtonArray[WindowArray[WindowName]->ButtonArray.size() - 1]->ButtonKinds = ButtonKinds;
	WindowArray[WindowName]->ButtonArray[WindowArray[WindowName]->ButtonArray.size() - 1]->Event = PushEvent;
	WindowArray[WindowName]->ButtonArray[WindowArray[WindowName]->ButtonArray.size() - 1]->Edge = false;
}

void ImguiLib::ImguiCreateWindow(std::string WindowName)
{
	if (WindowArray.count(WindowName) == 0)
	{
		WindowArray[WindowName] = new ImguiWindowConfig();
		WindowArray[WindowName]->WindowName = WindowName;
	}
	else
	{
		MessageBox(hWnd, L"WindowName is confliction", L"result", MB_ICONINFORMATION);
	}
	
}

void ImguiLib::ImguiCreateSliderF(std::string WindowName, std::string SliderName, float* SliderValue, float Min, float Max)
{
	WindowArray[WindowName]->SlliderArray.emplace_back(new SliderConfig());
	WindowArray[WindowName]->SlliderArray[WindowArray[WindowName]->SlliderArray.size() - 1]->SliderName = SliderName;
	WindowArray[WindowName]->SlliderArray[WindowArray[WindowName]->SlliderArray.size() - 1]->SliderValue = SliderValue;
	WindowArray[WindowName]->SlliderArray[WindowArray[WindowName]->SlliderArray.size() - 1]->Max = Max;
	WindowArray[WindowName]->SlliderArray[WindowArray[WindowName]->SlliderArray.size() - 1]->Min = Min;
}

void ImguiLib::ImguiCreateText(const char* Text, ...)
{
	
}

LRESULT ImguiLib::ImGuiProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;

	return 0;
}

ImguiLib::~ImguiLib()
{
}
