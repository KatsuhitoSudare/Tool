#pragma once
#include<Windows.h>
#include<d3d11.h>
#include<dxgi.h>
#include<GLFW/glfw3.h>



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
			static BOOL D3D11RenderingEnginInit();

			static void SetRenderTerget();

			static GLuint GetRenderedImage();

			static void MeshRender();

		private:
			static inline ID3D11Device*				m_pDevice;	/*DirectX11��Device*/
			static inline ID3D11DeviceContext*		m_pContext;	/*DirectX11��DeviceContext*/
			static inline ID3D11Texture2D*			m_pRenderingTergetTexture;	/*�����_�����O��ɂ���e�N�X�`��*/
			static inline ID3D11RenderTargetView*	m_rtv;
			static inline ID3D11DepthStencilView*	m_DSV;
			static inline ID3D11Texture2D*			m_DST;
			static inline UINT						m_RendertergetWidth,m_RenderTergetHeight;/*�����_�[�^�[�Q�b�g�̕�*/
		};
	}
}




