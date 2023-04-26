cbuffer MatrixBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};

cbuffer BoneTransformBuffer : register(b1)
{
    matrix boneTransforms[256];
};

struct VertexInputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL;
    int4 boneIndices : BONEINDICES;
    float4 boneWeights : BONEWEIGHTS;
};

struct PixelInputType
{
    float2 tex : TEXCOORD0;
    float4 normal : NORMAL;
    float4 position : SV_POSITION;
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;

   

    matrix comb = boneTransforms[input.boneIndices[0]] * input.boneWeights[0];
    comb += mul(comb, boneTransforms[input.boneIndices[1]] * input.boneWeights[1]);
    comb += mul(comb, boneTransforms[input.boneIndices[2]] * input.boneWeights[2]);
    comb += mul(comb, boneTransforms[input.boneIndices[3]] * input.boneWeights[3]);

    output.position = mul(float4(input.position, 1.0), comb);
    
    // ワールド座標系への変換
    output.position = mul(output.position, world);

    // 法線をワールド座標系に変換
    output.normal = mul(float4(input.normal, 0.0), comb);
    
    output.normal = mul(output.normal, world);

    // テクスチャ座標の設定
    output.tex = input.tex;

    // ビュー座標系への変換
    output.position = mul(output.position, view);

    // クリップ座標系への変換
    output.position = mul(output.position, projection);

    return output;
}
