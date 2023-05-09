#include	<DirectXMath.h>
#include	"CDirectxGraphics.h"
#include	"dx11helper.h"
#include "triangle.h"

using namespace DirectX;

// ���_�\����
struct Vertex {
	XMFLOAT3	Pos;
};

// �萔�o�b�t�@�\����
struct ConstantBuffer_Color {
	XMFLOAT4	Color;							// �J���[�l
};

ID3D11Buffer*			g_VertexBuffer = nullptr;	// ���_�o�b�t�@
ID3D11VertexShader*		g_VertexShader = nullptr;	// ���_�V�F�[�_�[
ID3D11PixelShader*		g_PixelShader = nullptr;	// �s�N�Z���V�F�[�_�[
ID3D11InputLayout*		g_VertexLayout = nullptr;	// ���_���C�A�E�g

ID3D11Buffer*			g_ConstantBuffer = nullptr;	// �萔�o�b�t�@

int                     g_vertexnum = 6;

// ��������
bool InitTrinagle() {

	ID3D11Device*		 device;

	// �f�o�C�X���擾����
	device = CDirectXGraphics::GetInstance()->GetDXDevice();

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// �G�������g��
	unsigned int numElements = ARRAYSIZE(layout);

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	bool sts = CreateVertexShader(			
		device,								// �f�o�C�X�I�u�W�F�N�g						
		"vstriangle.hlsl",					// ���_�V�F�[�_�[�\�[�X�t�@�C��					
		"main",								// �G���g���֐�
		"vs_5_0",							// ���_�V�F�[�_�[���f���T�D�O
		layout,								// ���_�f�[�^���C�A�E�g
		numElements,						// ���_�f�[�^�̃G�������g��
		&g_VertexShader,					// ���_�V�F�[�_�[�I�u�W�F�N�g
		&g_VertexLayout);					// ���_�f�[�^���C�A�E�g�I�u�W�F�N�g
	if (!sts) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}

	// �s�N�Z���V�F�[�_�[�𐶐�
	sts = CreatePixelShader(			// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
			device,						// �f�o�C�X�I�u�W�F�N�g
			"pstriangle.hlsl",			// �s�N�Z���V�F�[�_�[�\�[�X�t�@�C��
			"main",						// �G���g���֐�
			"ps_5_0",					// �s�N�Z���V�F�[�_�[���f���T�D�O
			&g_PixelShader);			// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	// ���_���W
	/*Vertex	v[3] = {
		XMFLOAT3(0.0f*2.0f, 0.25f*2.0f, 0.5f),
		XMFLOAT3(0.25f*2.0f, -0.25f*2.0f, 0.5f),
		XMFLOAT3(-0.25f*2.0f, -0.25f*2.0f, 0.5f)
	};*/

	 //���_���W�l�p�`�o�[�W����
	Vertex	v[6] = {
		XMFLOAT3(-0.5f, 0.5f, 0.5f),
		XMFLOAT3(0.5,   0.5f, 0.5f),
		XMFLOAT3(-0.5, -0.5f, 0.5f),
		XMFLOAT3(0.5f,  0.5f, 0.5f),
		XMFLOAT3(0.5,  -0.5f, 0.5f),
		XMFLOAT3(-0.5, -0.5f, 0.5f),
	};

	

	// ���_�o�b�t�@�𐶐�
	sts = CreateVertexBuffer(
		device,						// �f�o�C�X�I�u�W�F�N�g
		sizeof(Vertex),				// �P���_������o�C�g��
		g_vertexnum,				    // ���_��
		v,							// ���_�f�[�^�i�[�������擪�A�h���X
		&g_VertexBuffer				// ���_�o�b�t�@
	);



	if (!sts) {
		MessageBox(nullptr, "CreateVertexBuffer error", "error", MB_OK);
		return false;
	}

	// �萔�o�b�t�@�쐬(�������R�[�f�B���O)
	D3D11_BUFFER_DESC cbDesc{};

	cbDesc.ByteWidth = sizeof(ConstantBuffer_Color);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	device->CreateBuffer(&cbDesc, NULL, &g_ConstantBuffer);

	return true;
}

// �X�V����
void UpdateTriangle() {

	static float r = 0.0f;
	static float g = 0.0f;
	static float b = 0.0f;

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		r += 0.01f;
		if (r >= 1.0f) {
			r = 1.0f;
		}
	}
	if (GetAsyncKeyState(VK_F2) & 0x8000) {
		r -= 0.01f;
		if (r <= 0.0f) {
			r = 0.0f;
		}
	}

	if (GetAsyncKeyState(VK_F3) & 0x8000) {
		g += 0.01f;
		if (g >= 1.0f) {
			g = 1.0f;
		}
	}
	if (GetAsyncKeyState(VK_F4) & 0x8000) {
		g -= 0.01f;
		if (g <= 0.0f) {
			g = 0.0f;
		}
	}

	if (GetAsyncKeyState(VK_F5) & 0x8000) {
		b += 0.01f;
		if (b >= 1.0f) {
			b = 1.0f;
		}
	}
	if (GetAsyncKeyState(VK_F6) & 0x8000) {
		b -= 0.01f;
		if (b <= 0.0f) {
			b = 0.0f;
		}
	}

	// �R���X�^���g�o�b�t�@�\���̂փJ���[�l���Z�b�g
	ConstantBuffer_Color cb;
	cb.Color.x = r;			// r
	cb.Color.y = g;			// g
	cb.Color.z = b;			// b
	cb.Color.w = 1.0f;		// a

	// �f�o�C�X�R���e�L�X�g�擾
	ID3D11DeviceContext*		 devicecontext;		// �f�o�C�X�R���e�L�X�g															// �f�o�C�X�R���e�L�X�g���擾����
	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// �萔�o�b�t�@�X�V�i�������R�[�f�B���O�j
	devicecontext->UpdateSubresource(g_ConstantBuffer,0,NULL, &cb,0,0);

}

// �`�揈��
void DrawTriangle() {

	ID3D11DeviceContext*		 devicecontext;				// �f�o�C�X�R���e�L�X�g

	// �f�o�C�X�R���e�L�X�g���擾����
	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	unsigned int stride = sizeof(Vertex);					// �X�g���C�h���Z�b�g�i�P���_������̃o�C�g���j
	unsigned  offset = 0;									// �I�t�Z�b�g�l���Z�b�g

	// ���_�o�b�t�@���f�o�C�X�R���e�L�X�g�փZ�b�g
	devicecontext->IASetVertexBuffers(			
		0,													// �X�^�[�g�X���b�g
		1,													// ���_�o�b�t�@��
		&g_VertexBuffer,									// ���_�o�b�t�@�̐擪�A�h���X
		&stride,											// �X�g���C�h
		&offset);											// �I�t�Z�b�g

	// �g�|���W�[���Z�b�g
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ���_�t�H�[�}�b�g���Z�b�g
	devicecontext->IASetInputLayout(g_VertexLayout);

	devicecontext->VSSetShader(g_VertexShader, nullptr, 0);		// ���_�V�F�[�_�[���Z�b�g
	devicecontext->PSSetShader(g_PixelShader, nullptr, 0);		// �s�N�Z���V�F�[�_�[���Z�b�g

	
	// �萔�o�b�t�@��GPU�փZ�b�g�i�������R�[�f�B���O�j
	devicecontext->PSSetConstantBuffers(0, 1, &g_ConstantBuffer);


	// �f�o�C�X�R���e�L�X�g�ɒ��_�f�[�^�𗬂�����
	devicecontext->Draw(
		g_vertexnum,				// ���_��
		0);				            // �J�n���_�C���f�b�N�X
}

void DrawBox()
{
	ID3D11DeviceContext* devicecontext;				// �f�o�C�X�R���e�L�X�g

	// �f�o�C�X�R���e�L�X�g���擾����
	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	unsigned int stride = sizeof(Vertex);					// �X�g���C�h���Z�b�g�i�P���_������̃o�C�g���j
	unsigned  offset = 0;									// �I�t�Z�b�g�l���Z�b�g

	// ���_�o�b�t�@���f�o�C�X�R���e�L�X�g�փZ�b�g
	devicecontext->IASetVertexBuffers(
		0,													// �X�^�[�g�X���b�g
		1,													// ���_�o�b�t�@��
		&g_VertexBuffer,									// ���_�o�b�t�@�̐擪�A�h���X
		&stride,											// �X�g���C�h
		&offset);											// �I�t�Z�b�g

	// �g�|���W�[���Z�b�g
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ���_�t�H�[�}�b�g���Z�b�g
	devicecontext->IASetInputLayout(g_VertexLayout);

	devicecontext->VSSetShader(g_VertexShader, nullptr, 0);		// ���_�V�F�[�_�[���Z�b�g
	devicecontext->PSSetShader(g_PixelShader, nullptr, 0);		// �s�N�Z���V�F�[�_�[���Z�b�g


	// �萔�o�b�t�@��GPU�փZ�b�g�i�������R�[�f�B���O�j
	devicecontext->PSSetConstantBuffers(0, 1, &g_ConstantBuffer);


	// �f�o�C�X�R���e�L�X�g�ɒ��_�f�[�^�𗬂�����
	devicecontext->Draw(
		3,				// ���_��
		0);				// �J�n���_�C���f�b�N�X
}

// �I������
void UninitTriangle() {

	if (g_VertexLayout != nullptr) {
		g_VertexLayout->Release();
		g_VertexLayout = nullptr;
	}

	if (g_VertexShader != nullptr) {
		g_VertexShader->Release();
		g_VertexShader = nullptr;
	}

	if (g_PixelShader != nullptr) {
		g_PixelShader->Release();
		g_PixelShader = nullptr;
	}

	if (g_VertexBuffer != nullptr) {
		g_VertexBuffer->Release();
		g_VertexBuffer = nullptr;
	}

	if (g_ConstantBuffer != nullptr) {
		g_ConstantBuffer->Release();
		g_ConstantBuffer = nullptr;
	}
}