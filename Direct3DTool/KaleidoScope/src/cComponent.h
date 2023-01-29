#pragma once
#include "cObject.h"
#include"cTransform.h"

class cGameObject;


namespace KALEIDOSCOPE
{
	class cComponent : public cObject
	{
	public:
		cComponent();
		virtual ~cComponent();

		cTransform* m_Transform;
		cGameObject* m_GameObject;

	private:



	};
}



