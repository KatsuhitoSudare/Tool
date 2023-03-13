#pragma once
#include "cComponent.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"ConstantBuffer.h"


namespace KALEIDOSCOPE
{
	struct v
	{
		float x, y, z;		// �ʒu
		float r, g, b, a;	// ���_�F
		//	float nx, ny, nz;	// �@�����
		float u, v;			// �e�N�X�`��UV���W
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



