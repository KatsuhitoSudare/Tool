struct VSOutput
{
    float4 svpos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD; // 頂点シェーダーから来たuv
};

float4 pixel(VSOutput input) : SV_TARGET
{
    return float4(input.uv.xy, 1, 1);
}