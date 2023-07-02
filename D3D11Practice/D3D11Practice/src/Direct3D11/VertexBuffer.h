#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<vector>
#include"cDirect3D.h"
using Microsoft::WRL::ComPtr;

//======================================================================
// VertexBufferÇçÏê¨Ç∑ÇÈä÷êî
//======================================================================
template<class T>
class VertexBuffer
{
public:
	HRESULT CreateVertexBuffer(std::vector<T> const& VertexList);
    void IASetVertexBuffer(std::vector<T> Vertexlist);

private:
	ComPtr<ID3D11Buffer> Buffer;
};

template<class T>
inline HRESULT VertexBuffer<T>::CreateVertexBuffer(std::vector<T> const&  VertexList)
{
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.ByteWidth = sizeof(T) * (UINT)VertexList.size();
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    T* VertexDate = new T[VertexList.size()];

    for (int i = 0; i < VertexList.size(); i++)
    {
        VertexDate[i] = VertexList[i];
    }


    D3D11_SUBRESOURCE_DATA subResourceData;
    subResourceData.pSysMem = VertexDate;
    subResourceData.SysMemPitch = 0;
    subResourceData.SysMemSlicePitch = 0;

    auto hr = cDirect3D::GetDevice()->CreateBuffer(&bufferDesc, &subResourceData, Buffer.GetAddressOf());
    
    delete[] VertexDate;

    return S_OK;
}

template<class T>
inline void VertexBuffer<T>::IASetVertexBuffer(std::vector<T> Vertexlist)
{
    UINT strides = sizeof(T);
    UINT offsets = 0;

    cDirect3D::GetContext()->UpdateSubresource(Buffer.Get(), 0, NULL, Vertexlist.data(), 0, 0);
    cDirect3D::GetContext()->IASetVertexBuffers(0, 1, Buffer.GetAddressOf(), &strides, &offsets);
}
