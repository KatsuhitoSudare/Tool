#include "..\..\KALEIDOSCOPE\include\IndexBuffer.h"

HRESULT IndexBuffer::CreateIndexBuffer(ID3D11Device* _device, std::vector<UINT>& IndexList)
{
    D3D11_BUFFER_DESC ibDesc{};
    ibDesc.ByteWidth = sizeof(UINT) * IndexList.size();
    ibDesc.Usage = D3D11_USAGE_DEFAULT;
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibDesc.CPUAccessFlags = 0;
    ibDesc.MiscFlags = 0;
    ibDesc.StructureByteStride = 0;

    UINT* list = new UINT[IndexList.size()];

    for (int i = 0; i < IndexList.size(); i++)
    {
        list[i] = IndexList[i];
    }

    D3D11_SUBRESOURCE_DATA irData{};
    irData.pSysMem = list;
    irData.SysMemPitch = 0;
    irData.SysMemSlicePitch = 0;


    auto hr = _device->CreateBuffer(&ibDesc, &irData, &Buffer);
    if (FAILED(hr))
        return hr;

    NumIndex = *list;

    delete[] list;

    return S_OK;
}

UINT IndexBuffer::GetNumIndex()
{
    return NumIndex;
}

void IndexBuffer::IASetIndexBuffer(ID3D11DeviceContext* Context)
{
    if (Context != nullptr)
    {
        Context->IASetIndexBuffer(Buffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    }
}
