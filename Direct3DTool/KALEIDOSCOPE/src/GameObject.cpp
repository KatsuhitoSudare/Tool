#include "GameObject.h"
#include"cDirect3D.h"

#ifdef _DEBUG
#pragma comment(lib,"Direct3D11_debug.lib")
#else
#pragma comment(lib,"Direct3D11.lib")
#endif // _DEBUG

//���_�̏��
D3D11_INPUT_ELEMENT_DESC desc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��POSITION
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��NORMAL
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2��TEXCOORD
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3��TANGENT
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4��COLOR
};

void GameObject::Init()
{
	//ImportSettings importSetting = // ���ꎩ�͎̂���̓ǂݍ��ݐݒ�\����
	//{
	//	modelFile,
	//	meshes,
	//	false,
	//	true
	//};

	VS.InitVertexShader(L"Shader/VertexShader.hlsl", "vert", cDirect3D::GetDevice(), desc, ARRAYSIZE(desc));
	//PS.InitPixelShader(L"Shader/VertexShader", "vert", cDirect3D::GetDevice());

}

void GameObject::Draw()
{
}
