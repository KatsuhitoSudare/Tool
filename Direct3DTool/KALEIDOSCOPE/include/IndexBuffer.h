#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<vector>

using Microsoft::WRL::ComPtr;

class IndexBuffer
{
public:
	HRESULT CreateIndexBuffer(ID3D11Device* _device, std::vector<UINT>& IndexList);
	UINT GetNumIndex();
	void IASetIndexBuffer(ID3D11DeviceContext* Context);
private:
	ComPtr<ID3D11Buffer> Buffer;
	UINT NumIndex;
};