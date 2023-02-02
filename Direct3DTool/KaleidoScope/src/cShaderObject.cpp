#include "cShaderObject.h"
#include"cDirect3D.h"


namespace KALEIDOSCOPE
{
	cShaderObject::cShaderObject()
	{
	}

	cShaderObject::~cShaderObject()
	{
	}

	void cShaderObject::ShaderInit()
	{

	}

	void cShaderObject::SetShader(string ShaderName)
	{
		//static ID3D11Device* device =  cDirect3D::GetDevice();
		static ID3D11DeviceContext* context = cDirect3D::GetContext();

		context->

		context->VSSetShader(ShaderObjectArray[ShaderName]->m_VertexShader.Get(), NULL, 0);
		context->PSSetShader(ShaderObjectArray[ShaderName]->m_PixelShader.Get(),NULL,0);
		
	}

}


