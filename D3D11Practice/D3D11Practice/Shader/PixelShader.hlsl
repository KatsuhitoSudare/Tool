struct VSOutput
{
    float4 svpos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD; // ���_�V�F�[�_�[���痈��uv
};

float4 pixel(VSOutput input) : SV_TARGET
{
    return float4(input.uv.xy, 1, 1);
}