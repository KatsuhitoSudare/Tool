#pragma once
#include"Object.h"
#include"TransForm.h"

namespace KALEIDOSCOPE
{
	namespace COLLECTION
	{
		class GameObject : public Object
		{
		public:
			GameObject();
			GameObject(string Name);
			TransForm transform;
		};
	}
}


