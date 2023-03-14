#include "GameObject.h"
#include"cDirect3D.h"

#ifdef _DEBUG
#pragma comment(lib,"Direct3D11_debug.lib")
#else
#pragma comment(lib,"Direct3D11.lib")
#endif // _DEBUG

//í∏ì_ÇÃèÓïÒ
D3D11_INPUT_ELEMENT_DESC desc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3ÇÃPOSITION
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3ÇÃNORMAL
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float2ÇÃTEXCOORD
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3ÇÃTANGENT
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4ÇÃCOLOR
};

void GameObject::Init()
{
	//ImportSettings importSetting = // Ç±ÇÍé©ëÃÇÕé©çÏÇÃì«Ç›çûÇ›ê›íËç\ë¢ëÃ
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
