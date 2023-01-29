#pragma once
#include "cObject.h"

namespace KALEIDOSCOPE
{
	class cTransform : public cObject
	{
	public:
		cTransform();
		~cTransform();

		XMFLOAT3 m_Pos;
		XMFLOAT3 m_Scale;
		XMFLOAT3 m_Rotation;

	};
}



