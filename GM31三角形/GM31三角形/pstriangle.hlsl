//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

// �萔�o�b�t�@�\����
cbuffer ConstantBufferColor : register(b0)
{
	float4 color;
}

float4 main( ) : SV_Target
{
    ////���F���O�p�p
    return float4(1.0f,1.0f,0.0f,0.0f);
    
    //�萔�o�b�t�@�p
    //return color;
}
