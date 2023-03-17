#pragma once
#include"ImguiLib.h"
#include<string>

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class ViewManager
		{
		public:
			static void Inititalize();
			static void SutoDoun();
			static void Render();
		private:
			static inline std::string AssetsView;
			static inline std::string SceneView;
			static inline std::string GameView;
			static inline std::string HierarchyView;
			static inline std::string InspectorView;
			static inline std::string MasterWindow;

			static inline float f;
			static inline float fg;
		};
	}
}



