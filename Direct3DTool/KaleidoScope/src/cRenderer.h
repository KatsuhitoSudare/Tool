#pragma once
#include "cComponent.h"

namespace KALEIDOSCOPE
{
	class cRenderer :public cComponent
	{
	public:
		cRenderer();

		virtual ~cRenderer();

		virtual void OnRender(XMMATRIX _View,XMMATRIX _Projection);

	private:



	};
}



