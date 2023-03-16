#pragma once
#include<d3d11.h>


namespace KALEIDOSCOPE
{
	namespace GUI
	{
		class KS_WindowManager
		{
		public:
			static void Inititalize(ID3D11Device* device,ID3D11DeviceContext* context,HWND hWnd);
			static void Render();
			static void ShutDown();
		private:


		};
	}
}



