#pragma once
#include "Renderer.h"

namespace KALEIDOSCOPE
{
	namespace COLLECTION
	{
		class MeshRenderer :public Renderer
		{
		public:
			MeshRenderer();
			void Render()override;
		};
	}
}

