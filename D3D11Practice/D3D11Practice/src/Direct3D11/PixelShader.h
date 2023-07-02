#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

using Microsoft::WRL::ComPtr;

class PixelShader
{
public:
	HRESULT InitPixelShader(const wchar_t* FileName);
	void SetPixelShader();
private:
	ComPtr<ID3D11PixelShader> Shader;
};

