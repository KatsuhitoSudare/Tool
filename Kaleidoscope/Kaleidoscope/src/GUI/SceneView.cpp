#include "SceneView.h"
#include"..\IMGUI\imgui.h"
#include"..\Direct3D11\D3D11RenderingEngin.h"

namespace KALEIDOSCOPE
{
	namespace GUI
	{
		SceneView::SceneView()
		{
			WindowName = "Scene";
		}
		void SceneView::Update()
		{
			ImGui::Begin(WindowName.c_str(), &CloseButton);

			//�e�N�X�`�����󂯎��ϐ�
			D3D11_TEXTURE2D_DESC desc;
			ID3D11Texture2D* tex = RENDARINGENGIN::D3D11RenderingEngin::GetRenderTexture();
			tex->GetDesc(&desc);

			UINT Width = desc.Width;
			UINT height = desc.Height;
			UINT rowPitch = desc.Width * 4;//RGBa�t�H�[�}�b�g�Ɖ��肵��
			UINT slicePitch = rowPitch * desc.Height;
			BYTE* textureData = new BYTE[slicePitch];
			ID3D11DeviceContext*  context;
			tex->GetDevice()


			ImGui::End();
		}
	}
}