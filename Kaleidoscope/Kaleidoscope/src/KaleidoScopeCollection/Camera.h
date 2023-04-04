#pragma once
#include"TransForm.h"
#include<DirectXMath.h>

namespace KALEIDOSCOPE
{
	namespace COLLECTION
	{
		class Camera
		{
		public:
			Camera();
			TransForm transform;
			DirectX::XMMATRIX GetViewMatrix();
			DirectX::XMMATRIX GetProjectionMatrix();
			void SetFov(float Fov);
			void SetGazePoint(DirectX::XMVECTOR GazePoint);
			void SetUpwardVec(DirectX::XMVECTOR Upward);
		private:
			DirectX::XMVECTOR GazePoint;//�����_
			DirectX::XMVECTOR UpwardVec;//������x�N�g��
			DirectX::XMMATRIX View;//�r���[�s��
			DirectX::XMMATRIX Projection;//�v���W�F�N�V�����s��
			float             FovAngle;
		};
	}
}


