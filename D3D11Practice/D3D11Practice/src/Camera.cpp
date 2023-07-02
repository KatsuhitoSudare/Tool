#include "Camera.h"

void Camera::CreateCamera(float x, float y, float z)
{
	DirectX::XMVECTOR Eyepos = DirectX::XMVectorSet(x, y, z,0.0f);
	DirectX::XMVECTOR forcas = DirectX::XMVectorSet(0.0f, 0.0f, 0.0, 0.0f);
	DirectX::XMVECTOR Up =	DirectX::XMVectorSet(0.0f,1.0f,0.0f,0.0f);

	View =  DirectX::XMMatrixLookAtLH(Eyepos,forcas,Up);

	Proje = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), 16 / 9, 0.0, 1000.0f);

	if (maincamera != nullptr)
	{
		maincamera = this;
	}
}

DirectX::XMMATRIX Camera::GetViewMat()
{
	using namespace DirectX;
	DirectX::XMVECTOR Eyepos = DirectX::XMVectorSet(
		XMVectorGetX(trunsform.GetPosition()),
		XMVectorGetY(trunsform.GetPosition()),
		XMVectorGetZ(trunsform.GetPosition()),
				0.0f);

	DirectX::XMVECTOR forcas = DirectX::XMVectorSet(0.0f, 0.0f, 0.0, 0.0f);
	DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	return View = DirectX::XMMatrixLookAtLH(Eyepos, forcas, Up);
}

DirectX::XMMATRIX Camera::GetProjectionMat()
{
	return Proje;
}
