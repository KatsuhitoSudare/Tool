#pragma once
#include "cComponent.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"ConstantBuffer.h"


namespace KALEIDOSCOPE
{
	struct v
	{
		float x, y, z;		// 位置
		float r, g, b, a;	// 頂点色
		//	float nx, ny, nz;	// 法線情報
		float u, v;			// テクスチャUV座標
	};

	struct Constant
	{
		XMMATRIX w;
		XMMATRIX v;
		XMMATRIX p;
	};

	class cRenderer :public cComponent
	{
	public:
		cRenderer();
		cRenderer(ID3D11Device* device);

		virtual ~cRenderer();

		virtual void OnRender(XMMATRIX _View,XMMATRIX _Projection);

	private:
		VertexBuffer<v>* Vertex;
		IndexBuffer* Index;
		ConstantBuffer<Constant>* Cbuff;
	};
}



