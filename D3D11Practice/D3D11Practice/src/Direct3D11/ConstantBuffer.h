#pragma once
#include"cDirect3D.h"
#include<d3d11.h>
#include<wrl/client.h>
#include<vector>

using Microsoft::WRL::ComPtr;

template<class T>
class ConstantBuffer
{
public:
	HRESULT CreateConstantBuffer();
    void UpdateBufferResource(T* NewResource);
    void VSSetConstantBuffer(int slot);
private:
	ComPtr<ID3D11Buffer> Buffer;
};


template<class T>
inline HRESULT ConstantBuffer<T>::CreateConstantBuffer()
{
    D3D11_BUFFER_DESC cbDesc{};

    cbDesc.ByteWidth = sizeof(T);
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    auto hr = cDirect3D::GetDevice()->CreateBuffer(&cbDesc, NULL, &Buffer);
    if (FAILED(hr))
        return hr;

	return S_OK;
}

template<class T>
inline void ConstantBuffer<T>::UpdateBufferResource(T* NewResource)
{
    cDirect3D::GetContext()->UpdateSubresource(Buffer.Get(), 0, NULL, NewResource, 0, 0);
}

template<class T>
inline void ConstantBuffer<T>::VSSetConstantBuffer(int slot)
{
    cDirect3D::GetContext()->VSSetConstantBuffers(slot, 1, Buffer.GetAddressOf());
}
