#pragma once
#include "Renderer.h"



class MeshRenderer :public Renderer
{
public:
	using Renderer::Renderer;
	~MeshRenderer();
	void Init()override;
	void Render()override;
private:

};

