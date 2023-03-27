#pragma once
#include<Windows.h>
#include<d3d11.h>
#include<dxgi.h>

//=================================================
// D3D11�̃����_�����O�̋@�\�݂̂��������N���X
//=================================================
namespace KALEIDOSCOPE
{
	namespace RENDARINGENGIN
	{
		class D3D11RenderingEngin
		{
		public:
			//�R���X�g���N�^
			D3D11RenderingEngin();
			//�f�X�g���N�^
			~D3D11RenderingEngin();
			//�������֐�
			BOOL D3D11RenderingEnginInit();

		private:
			ID3D11Device*		    m_pDevice;	/*DirectX11��Device*/
			ID3D11DeviceContext*    m_pContext;	/*DirectX11��DeviceContext*/
			ID3D11Texture2D*        m_pRenderingTergetTexture;	/*�����_�����O��ɂ���e�N�X�`��*/
			ID3D11RenderTargetView* m_rtv;
			ID3D11DepthStencilView* m_DSV;
			ID3D11Texture2D*		m_DST;
			UINT					m_RendertergetWidth,m_RenderTergetHeight;/*�����_�[�^�[�Q�b�g�̕�*/
		};
	}
}




