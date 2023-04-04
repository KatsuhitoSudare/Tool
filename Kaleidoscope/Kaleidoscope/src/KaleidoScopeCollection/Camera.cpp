#include "Camera.h"

namespace KALEIDOSCOPE
{
	namespace COLLECTION
	{
		Camera::Camera()
		{
			FovAngle = DirectX::XM_PIDIV4;
			View = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat4(&transform.Pos), GazePoint, UpwardVec);
			Projection = DirectX::XMMatrixPerspectiveFovLH(FovAngle, 16.0f / 9.0f, 0.1f,1000.0f);
		}
		DirectX::XMMATRIX Camera::GetViewMatrix()
		{
			View = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat4(&transform.Pos), GazePoint, UpwardVec);
			return View;
		}
		DirectX::XMMATRIX Camera::GetProjectionMatrix()
		{
			Projection = DirectX::XMMatrixPerspectiveFovLH(FovAngle, 16.0f / 9.0f, 0.1f, 1000.0f);
			return Projection;
		}
		void Camera::SetFov(float Fov)
		{
			FovAngle = Fov;
		}
		void Camera::SetGazePoint(DirectX::XMVECTOR GazePoint)
		{
			this->GazePoint = GazePoint;
		}
		void Camera::SetUpwardVec(DirectX::XMVECTOR Upward)
		{
			this->UpwardVec = Upward;
		}
	}
}