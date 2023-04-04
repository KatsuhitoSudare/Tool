#pragma once
#include<DirectXMath.h>

namespace KALEIDOSCOPE
{
	namespace COLLECTION
	{
		class TransForm
		{
		public:
			TransForm();
			DirectX::XMVECTOR Pos;
			DirectX::XMVECTOR Scale;
			DirectX::XMVECTOR Rotate;
		};
	}
}


