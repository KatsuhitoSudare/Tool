//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
struct VS_OUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};


// 定数バッファ構造体
cbuffer ConstantBufferColor : register(b0)
{
	float4 color;
}

float4 main(VS_OUT input) : SV_Target
{
    ////黄色い三角用
    return input.Color;
    
    //定数バッファ用
    //return color;
}
