cbuffer Transform : register(b1)
{
    matrix World;
    matrix View;
    matrix Proj;
}

struct VSInput
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float3 tangent : TANGENT;
    float4 color : COLOR;
};

struct VSOutput
{
    float4 svpos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD; 
};

VSOutput vert(VSInput input)
{
    VSOutput output = (VSOutput) 0;

    output.svpos = float4(input.pos, 1.0f);
    output.svpos = mul(output.svpos,World);
    output.svpos = mul(output.svpos, View);
    output.svpos = mul(output.svpos,Proj);

    output.color = input.color;
    output.uv = input.uv; 
    return output;
}