#pragma once
#include "Window.h"
#include"..\KaleidoScopeCollection\GameObject.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class HierarchyView :public Window
		{
		public:
			HierarchyView();
			void Update()override;
		private:
			vector<KALEIDOSCOPE::COLLECTION::GameObject*> *ObjectArray;
		};
	}
}



