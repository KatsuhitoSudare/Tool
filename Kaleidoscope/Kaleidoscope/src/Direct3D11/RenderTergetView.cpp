#include "RenderTergetView.h"
#include<Windows.h>


//void RenderTergetView::CreateRenderTerget(ID3D11Texture2D* const Terget, UINT w, UINT h)
//{
//	//auto device;
//
//	//device->CreateRenderTargetView(Terget, NULL, &m_RTV);
//
//	////深度ステンシルバッファ作成
//	//D3D11_TEXTURE2D_DESC txDesc;
//
//	//ZeroMemory(&txDesc, sizeof(txDesc));
//	//txDesc.Width = w;
//	//txDesc.Height = h;
//	//txDesc.MipLevels = 1;
//	//txDesc.ArraySize = 1;
//	//txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//	//txDesc.SampleDesc.Count = 1;
//	//txDesc.SampleDesc.Quality = 0;
//	//txDesc.Usage = D3D11_USAGE_DEFAULT;
//	//txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//	//txDesc.CPUAccessFlags = 0;
//	//txDesc.MiscFlags = 0;
//
//	//auto hr = device->CreateTexture2D(&txDesc, NULL, &m_DST);
//	//if (SUCCEEDED(hr)) {
//	//	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
//	//	ZeroMemory(&dsDesc, sizeof(dsDesc));
//	//	dsDesc.Format = txDesc.Format;
//	//	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
//	//	dsDesc.Texture2D.MipSlice = 0;
//	//	hr = device->CreateDepthStencilView(m_DST.Get(), &dsDesc, &m_DSV);
//	//}
//
//}



//void RenderTergetView::SetRenderTerget(bool Zbufferflg)
//{
//	if (Zbufferflg)
//	{
//		if (m_DSV)
//		{
//			cDirect3D::GetContext()->OMSetRenderTargets(1,m_RTV.GetAddressOf(), m_DSV.Get());
//		}
//	}
//	else
//	{
//		cDirect3D::GetContext()->OMSetRenderTargets(1, m_RTV.GetAddressOf(), NULL);
//	}
//	
//}
//
//void RenderTergetView::ClearRenderTarget(float R, float G, float B)
//{
//	float clearColor[4] = { R, G, B, 1.0f }; //red,green,blue,alpha
//
//	cDirect3D::GetContext()->ClearRenderTargetView(m_RTV.Get(), clearColor);
//
//	// Zバッファ、ステンシルバッファクリア
//	cDirect3D::GetContext()->ClearDepthStencilView(
//		m_DSV.Get(),			// デプスステンシルビュー
//		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
//		1.0f,			// Ｚバッファを1.0でクリアする(0.0f～1.0f)
//		0);				// ステンシルバッファを0でクリアする
//}
//
//void RenderTergetView::CleanupRenderTarget()
//{
//	if (m_RTV) {
//		m_RTV.Reset();
//		m_DSV.Reset();
//		m_DST.Reset();
//	}
//}
