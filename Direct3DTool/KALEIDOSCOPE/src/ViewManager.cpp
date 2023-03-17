#include "ViewManager.h"
#include"ImguiLib.h"
#include"cDirect3D.h"
#include"cWindowManager.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		void ViewManager::Inititalize()
		{
			AssetsView = "AssetsView";
			SceneView  = "SceneView";
			GameView   = "GameView";
			HierarchyView = "HierarchyView";
			InspectorView = "InspectorView";
			MasterWindow  = "MasterWindow";

			IMGUILIB->Initialize(cWindowManager::GetWindowHandole(),cDirect3D::GetDevice(),cDirect3D::GetContext());
			//IMGUILIB->ImguiCreateWindowEX(MasterWindow, NoResize | NoTitleBar);
			IMGUILIB->ImguiCreateWindow(SceneView);
			IMGUILIB->ImguiCreateWindow(GameView);
			IMGUILIB->ImguiCreateWindow(HierarchyView);
			IMGUILIB->ImguiCreateWindow(InspectorView);
			IMGUILIB->ImguiCreateWindow(AssetsView);
			IMGUILIB->ImguiCreateSliderF(SceneView, "f", &f, 100, 1000);
			IMGUILIB->ImguiCreateSliderF(GameView, "fss", &fg, 100, 1000);
		}
		void ViewManager::SutoDoun()
		{
			IMGUILIB->Shutdown();
		}
		void ViewManager::Render()
		{
			IMGUILIB->ImguiRender();
		}
	}
}
