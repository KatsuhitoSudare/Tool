struct VS_OUT
{
    float4 pos;
    float2 UV;
    float3 Normal;
};

float4 main(VS_OUT input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}