/*****************************************************************//**
 * \file   GuiWindowManager.h
 * \brief  
 * 
 * \author 簾勝仁
 * \date   May 2023
 *********************************************************************/
#pragma once
#include<vector>
#include"Window.h"
#include"WindowHost.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{		
		class GuiWindowManager
		{
		public:
			static void InitializeGuiWindowAll();
			static void UpdateGuiWindowAll();
			static void RenderGuiWindowAll();
			static void ShutDownGuiWindowAll();
			static void* GetSelectObject();
			static void SetSelectObject(void * select);
		private:
			static void ImGuiInit();
			static inline void* SelectObject;//選択状態になったオブジェクトをインスペクタービューに伝えるためのポインタ
			static inline std::vector<Window*> WindowArray;
		};
	}
}



