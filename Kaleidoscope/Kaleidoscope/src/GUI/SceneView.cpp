#include "SceneView.h"
#include"..\IMGUI\imgui.h"
#include"..\IMGUI\imgui_impl_glfw.h"
#include"..\IMGUI\imgui_impl_opengl3.h"
#include"..\Direct3D11\D3D11RenderingEngin.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		SceneView::SceneView()
		{
			WindowName = "Scene";
		}
		void SceneView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);
			
			ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(RENDARINGENGIN::D3D11RenderingEngin::GetRenderedImage())),ImGui::GetContentRegionAvail());

			ImGui::End();
		}
	}
}