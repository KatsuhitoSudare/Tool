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
			DirectX::XMFLOAT4 Pos;
			DirectX::XMFLOAT4 Scale;
			DirectX::XMFLOAT4 Rotate;
		};
	}
}


