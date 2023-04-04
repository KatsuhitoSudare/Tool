#pragma once
#include<Windows.h>
#include"Window.h"
#include"..\KaleidoScopeCollection\GameObject.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class WindowHost : public Window
		{
		public:
			WindowHost();
			void Update()override;
		private:
			void SaveGameObject(KALEIDOSCOPE::COLLECTION::GameObject* _SaveGameObject);
		};
	}
}


