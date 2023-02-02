#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<vector>
#include<memory>
#include<map>
#include<string>
#include<DirectXMath.h>

using Microsoft::WRL::ComPtr;
using std::vector;
using std::unique_ptr;
using std::map;
using std::string;
using namespace DirectX;

struct VERTEXINFO
{
    XMFLOAT3 m_Pos;
    XMFLOAT2 m_UV;
    XMFLOAT3 m_Normal;
};


struct ShaderInfo
{
    ComPtr<ID3D11VertexShader>   m_VertexShader;
    ComPtr<ID3D11PixelShader>    m_PixelShader;
    ComPtr<ID3D11GeometryShader> m_GeometryShader;
    ComPtr<ID3D11BlendState>     m_BlendState;
    ComPtr<ID3D11RasterizerState>m_RasterizerState;
    ComPtr<ID3D11SamplerState>   m_SamplerState;
};


namespace KALEIDOSCOPE
{
    class cShaderObject
    {
    public:
        cShaderObject();
        ~cShaderObject();

        virtual void ShaderInit();

        void SetShader(string ShaderName);



    private:
        static map<string, unique_ptr<ShaderInfo>> ShaderObjectArray;
    };

}

