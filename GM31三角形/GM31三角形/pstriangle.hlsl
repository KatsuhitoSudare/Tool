//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
struct VS_OUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};


// �萔�o�b�t�@�\����
cbuffer ConstantBufferColor : register(b0)
{
	float4 color;
}

float4 main(VS_OUT input) : SV_Target
{
    ////���F���O�p�p
    return input.Color;
    
    //�萔�o�b�t�@�p
    //return color;
}
