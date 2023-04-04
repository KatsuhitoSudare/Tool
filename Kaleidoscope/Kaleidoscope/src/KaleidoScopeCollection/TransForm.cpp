#include "TransForm.h"


namespace KALEIDOSCOPE
{
	namespace COLLECTION
	{
		TransForm::TransForm()
		{
			Pos = DirectX::XMFLOAT4();
			Scale = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,0.0f);
			Rotate = DirectX::XMFLOAT4();
		}
	}
}

