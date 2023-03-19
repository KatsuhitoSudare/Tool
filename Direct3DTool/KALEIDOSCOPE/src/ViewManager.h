#pragma once
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
			static void SetMasterviewSize(float w,float h);
		private:
			static inline std::string AssetsView;
			static inline std::string SceneView;
			static inline std::string GameView;
			static inline std::string HierarchyView;
			static inline std::string InspectorView;
			static inline std::string MasterWindow;
			static inline float winde, height;
		};
	}
}



