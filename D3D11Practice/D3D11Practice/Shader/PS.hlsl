struct PixelInputType
{
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float4 position : SV_POSITION;
    float3 worldPos : TEXCOORD1;
};

// ディレクションライト用のデータを受け取るための定数バッファーを用意する
cbuffer DirectionLightCb : register(b1)
{
    float3 ligDirection; //ライトの方向
    float3 ligColor; //ライトのカラー

    // step-3 視点のデータにアクセスするための変数を定数バッファーに追加する
    float3 eyePos; //視点の位置
};

///////////////////////////////////////////
// シェーダーリソース
///////////////////////////////////////////
// モデルテクスチャ
Texture2D<float4> g_texture : register(t0);

///////////////////////////////////////////
// サンプラーステート
///////////////////////////////////////////
sampler g_sampler : register(s0);


float4 main(PixelInputType input) : SV_TARGET
{
     // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(input.normal, ligDirection);
    t *= -1.0f;
  
    // 内積の結果が0以下なら0にする
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    
    // 拡散反射光を求める
    float3 diffuseLig = ligColor * t;

    // step-4 反射ベクトルを求める
    float3 refVec = reflect(ligDirection, input.normal);

    // step-5 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = eyePos - input.worldPos;
    toEye = normalize(toEye);

    // step-6 鏡面反射の強さを求める
    t = dot(refVec, toEye);
    if (t < 0.0f)
    {
        t = 0.0f;
    }

    // step-7 鏡面反射の強さを絞る
    t = pow(t, 5.0f);

    // step-8 鏡面反射光を求める
    float3 specularLig = ligColor * t;

    // step-9 拡散反射光と鏡面反射光を足し算して、最終的な光を求める
    float3 lig = diffuseLig + specularLig;
    float4 finalColor = g_texture.Sample(g_sampler, input.tex);

    // step-10 テクスチャカラーに求めた光を乗算して最終出力カラーを求める
    finalColor.xyz *= lig;

    return finalColor;
}