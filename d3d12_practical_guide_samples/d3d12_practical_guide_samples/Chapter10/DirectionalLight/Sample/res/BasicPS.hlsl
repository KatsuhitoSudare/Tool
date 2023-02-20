//-----------------------------------------------------------------------------
// File : BasicPS.hlsl
// Desc : Pixel Shader.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "BRDF.hlsli"


///////////////////////////////////////////////////////////////////////////////
// VSOutput structure
///////////////////////////////////////////////////////////////////////////////
struct VSOutput
{
    float4      Position        : SV_POSITION;          // �ʒu���W�ł�.
    float2      TexCoord        : TEXCOORD;             // �e�N�X�`�����W�ł�.
    float3      WorldPos        : WORLD_POS;            // ���[���h��Ԃ̈ʒu���W�ł�.
    float3x3    InvTangentBasis : INV_TANGENT_BASIS;    // �ڐ���Ԃւ̊��ϊ��s��̋t�s��ł�.
};

///////////////////////////////////////////////////////////////////////////////
// PSOutput structure
///////////////////////////////////////////////////////////////////////////////
struct PSOutput
{
    float4  Color : SV_TARGET0;     // �o�̓J���[�ł�.
};

///////////////////////////////////////////////////////////////////////////////
// LightBuffer 
///////////////////////////////////////////////////////////////////////////////
cbuffer LightBuffer : register(b1)
{
    float3 LightColor       : packoffset(c0);     // ���C�g�J���[�ł�.
    float  LightIntensity   : packoffset(c0.w);   // ���C�g���x�ł�.
    float3 LightForward     : packoffset(c1);     // ���C�g�̏Ǝ˕����ł�.
};

///////////////////////////////////////////////////////////////////////////////
// CameraBuffer
///////////////////////////////////////////////////////////////////////////////
cbuffer CameraBuffer : register(b2)
{
    float3 CameraPosition : packoffset(c0);     // �J�����ʒu�ł�.
}

//-----------------------------------------------------------------------------
// Textures and Samplers
//-----------------------------------------------------------------------------
Texture2D       BaseColorMap : register(t0);
SamplerState    BaseColorSmp : register(s0);

Texture2D       MetallicMap  : register(t1);
SamplerState    MetallicSmp  : register(s1);

Texture2D       RoughnessMap : register(t2);
SamplerState    RoughnessSmp : register(s2);

Texture2D       NormalMap    : register(t3);
SamplerState    NormalSmp    : register(s3);


//-----------------------------------------------------------------------------
//      �s�N�Z���V�F�[�_�̃��C���G���g���[�|�C���g�ł�.
//-----------------------------------------------------------------------------
PSOutput main(VSOutput input)
{
    PSOutput output = (PSOutput)0;

    float3 L = normalize(LightForward);
    float3 V = normalize(CameraPosition - input.WorldPos);
    float3 H = normalize(V + L);
    float3 N = NormalMap.Sample(NormalSmp, input.TexCoord).xyz * 2.0f - 1.0f;
    N = mul(input.InvTangentBasis, N);

    float NV = saturate(dot(N, V));
    float NH = saturate(dot(N, H));
    float NL = saturate(dot(N, L));

    float3 baseColor = BaseColorMap.Sample(BaseColorSmp, input.TexCoord).rgb;
    float  metallic  = MetallicMap .Sample(MetallicSmp,  input.TexCoord).r;
    float  roughness = RoughnessMap.Sample(RoughnessSmp, input.TexCoord).r;

    float3 Kd      = baseColor * (1.0f - metallic);
    float3 diffuse = ComputeLambert(Kd);

    float3 Ks       = baseColor * metallic;
    float3 specular = ComputeGGX(Ks, roughness, NH, NV, NL);

    float3 BRDF = (diffuse + specular);

    output.Color.rgb = BRDF * NL * LightColor.rgb * LightIntensity;
    output.Color.a   = 1.0f;

    return output;
}