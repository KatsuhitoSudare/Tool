#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<vector>
#include<d3dcompiler.h>
#include<DirectXMath.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using Microsoft::WRL::ComPtr;

//í∏ì_ç\ë¢ëÃ
struct VertexInfo
{
	XMFLOAT3 Pos;
	XMFLOAT2 UV;
	XMFLOAT3 Nol;
};

//
class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	HRESULT InitVertexShader(const wchar_t* FileName,const char* EntryPoint, ID3D11Device* _device, D3D11_INPUT_ELEMENT_DESC* desc, int descsize);

	void SetVertexShaderAndInputLayout(ID3D11DeviceContext* context);
private:
	ComPtr<ID3D11VertexShader> Shader;
	ComPtr<ID3D11InputLayout> InputLayout;
	
};

