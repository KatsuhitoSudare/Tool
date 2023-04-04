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
			DirectX::XMVECTOR GazePoint;//注視点
			DirectX::XMVECTOR UpwardVec;//上向きベクトル
			DirectX::XMMATRIX View;//ビュー行列
			DirectX::XMMATRIX Projection;//プロジェクション行列
			float             FovAngle;
		};
	}
}


