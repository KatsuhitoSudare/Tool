/*****************************************************************//**
 * \file   GuiWindowManager.h
 * \brief  
 * 
 * \author �����m
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
			static inline void* SelectObject;//�I����ԂɂȂ����I�u�W�F�N�g���C���X�y�N�^�[�r���[�ɓ`���邽�߂̃|�C���^
			static inline std::vector<Window*> WindowArray;
		};
	}
}



