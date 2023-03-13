#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<vector>

using Microsoft::WRL::ComPtr;

template<class T>
class ConstantBuffer
{
public:
	HRESULT CreateConstantBuffer(ID3D11Device* _device);
    void UpdateBufferResource(T* NewResource,ID3D11DeviceContext* context);
    void VSSetConstantBuffer(ID3D11DeviceContext* context,int slot);
private:
	ComPtr<ID3D11Buffer> Buffer;
};


template<class T>
inline HRESULT ConstantBuffer<T>::CreateConstantBuffer(ID3D11Device* _device)
{
    D3D11_BUFFER_DESC cbDesc{};

    cbDesc.ByteWidth = sizeof(T);
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    auto hr = _device->CreateBuffer(&cbDesc, NULL, &Buffer);
    if (FAILED(hr))
        return hr;

	return S_OK;
}

template<class T>
inline void ConstantBuffer<T>::UpdateBufferResource(T* NewResource, ID3D11DeviceContext* context)
{
    D3D11_MAPPED_SUBRESOURCE pData;

    if (context != nullptr)
    {
        auto hr = context->Map(Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
        if (SUCCEEDED(hr))
        {
            memccpy(pData.pData, pData.RowPitch, NewResource, sizeof(T));
            context->Unmap(Buffer.Get(), 0);
        }
    }
}

template<class T>
inline void ConstantBuffer<T>::VSSetConstantBuffer(ID3D11DeviceContext* context, int slot)
{
    if (context != nullptr)
    {
        context->VSSetConstantBuffers(slot, 1, Buffer);
    }
}
