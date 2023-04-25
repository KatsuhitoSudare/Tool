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

    //// 頂点位置と法線の初期値
    //float4 localPosition = float4(0.0, 0.0, 0.0, 0.0);
    //float4 localNormal = float4(0.0, 0.0, 0.0, 0.0);

    //// スキニング処理
    //for (int i = 0; i < 4; ++i)
    //{
    //    float weight = input.boneWeights[i];
    //    if (weight > 0.0)
    //    {
    //        int boneIndex = input.boneIndices[i];
    //        matrix boneTransform = boneTransforms[boneIndex];
    //        float4 skinnedPosition = mul(float4(input.position, 1.0), boneTransform);
    //        float4 skinnedNormal = mul(float4(input.normal, 0.0), boneTransform);

    //        localPosition += skinnedPosition * weight;
    //        localNormal += skinnedNormal * weight;
    //    }
    //}

    // ワールド座標系への変換
    output.position = mul(float4(input.position, 1.0),world);

    // 法線をワールド座標系に変換
    output.normal = mul(float4(input.normal,1.0), world);

    // テクスチャ座標の設定
    output.tex = input.tex;

    // ビュー座標系への変換
    output.position = mul(output.position, view);

    // クリップ座標系への変換
    output.position = mul(output.position, projection);

    return output;
}
