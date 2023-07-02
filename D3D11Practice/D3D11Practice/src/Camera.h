#pragma once
#include"Trunsform.h"
#include<DirectXMath.h>

class Camera
{
public:
	void CreateCamera(float x, float y, float z);
	DirectX::XMMATRIX GetViewMat();
	DirectX::XMMATRIX GetProjectionMat();

	Trunsform trunsform;
	static inline Camera* maincamera;

private:
	DirectX::XMMATRIX View;
	DirectX::XMMATRIX Proje;
};