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
};

struct PixelInputType
{
    float2 tex : TEXCOORD0;
    float4 normal : NORMAL;
    float4 position : SV_POSITION;
    float3 worldPos : TEXCOORD1;
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    
    output.position = mul(world, float4(input.position, 0.0f)); // モデルの頂点をワールド座標系に変換
    output.worldPos = input.position;
    output.position = mul(view, output.position); // ワールド座標系からカメラ座標系に変換
    output.position = mul(projection, output.position); // カメラ座標系からスクリーン座標系に変換

    // 頂点法線をピクセルシェーダーに渡す
    output.normal = mul(world, float4(input.normal,0.0f)); // 法線を回転させる
    output.tex = input.tex;

    return output;
}
