#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

using Microsoft::WRL::ComPtr;

class PixelShader
{
public:
	HRESULT InitPixelShader(const wchar_t* FileName, const char* EntryPoint, ID3D11Device* _device);
	void SetPixelShader(ID3D11DeviceContext* context);
private:
	ComPtr<ID3D11PixelShader> Shader;
};

