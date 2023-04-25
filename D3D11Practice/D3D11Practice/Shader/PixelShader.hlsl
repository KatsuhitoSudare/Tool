struct PixelInputType
{
    float2 tex : TEXCOORD0;
    float4 normal : NORMAL;
    float4 position : SV_POSITION;
};

float4 main(PixelInputType input) : SV_TARGET
{
    return float4(input.tex,0.0,0.0);
}