//-----------------------------------------------------------------------------
// File : BasicPS.hlsl
// Desc : Pixel Shader.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "BRDF.hlsli"

#ifndef MIN_DIST
#define MIN_DIST (0.01)
#endif//MIN_DIST

#ifndef OPTIMIZATION
#define OPTIMIZATION (1)
#endif//OPTIMIZATION


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
// CbLight constant buffer.
///////////////////////////////////////////////////////////////////////////////
cbuffer CbLight : register(b1)
{
    float3  LightPosition       : packoffset(c0);
    float   LightInvSqrRadius   : packoffset(c0.w);
    float3  LightColor          : packoffset(c1);
    float   LightIntensity      : packoffset(c1.w);
};

///////////////////////////////////////////////////////////////////////////////
// CameraBuffer
///////////////////////////////////////////////////////////////////////////////
cbuffer CbCamera : register(b2)
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
//      ���������Ɋ��炩�Ɍ��������܂�.
//-----------------------------------------------------------------------------
float SmoothDistanceAttenuation
(
    float squaredDistance,      // ���C�g�ւ̋�����2��.
    float invSqrAttRadius       // ���C�g���a��2��̋t��.
)
{
    float  factor = squaredDistance * invSqrAttRadius;
    float  smoothFactor = saturate(1.0f - factor * factor);
    return smoothFactor * smoothFactor;
}

#ifndef OPTIMIZATION
//-----------------------------------------------------------------------------
//      �������������߂܂�.
//-----------------------------------------------------------------------------
float GetDistanceAttenuation(float3 unnormalizedLightVector)
{
    float sqrDist = dot(unnormalizedLightVector, unnormalizedLightVector);
    float attenuation = 1.0f / (max(sqrDist, MIN_DIST * MIN_DIST));
    return attenuation;
}

//-----------------------------------------------------------------------------
//      �|�C���g���C�g��]�����܂�.
//-----------------------------------------------------------------------------
float3 EvaluatePointLight
(
    float3      N,                      // �@���x�N�g��.
    float3      worldPos,               // ���[���h��Ԃ̃I�u�W�F�N�g�ʒu.
    float3      lightPos,               // ���C�g�̈ʒu.
    float3      lightColor              // ���C�g�J���[.
)
{
    float3 dif = lightPos - worldPos;
    float3 L = normalize(dif);
    float  att = GetDistanceAttenuation(dif);

    return saturate(dot(N, L)) * lightColor * att / (4.0f * F_PI);
}
#else
//-----------------------------------------------------------------------------
//      �������������߂܂�.
//-----------------------------------------------------------------------------
float GetDistanceAttenuation
(
    float3  unnormalizedLightVector,    // ���C�g�ʒu�ƃI�u�W�F�N�g�ʒu�̍����x�N�g��.
    float   invSqrAttRadius             // ���C�g���a��2��̋t��.
)
{
    float sqrDist = dot(unnormalizedLightVector, unnormalizedLightVector);
    float attenuation = 1.0f / (max(sqrDist, MIN_DIST * MIN_DIST));

    // ���֐��ɂ���Ċ��炩�Ƀ[���ƂȂ�悤�ɂ���
    attenuation *= SmoothDistanceAttenuation(sqrDist, invSqrAttRadius);

    return attenuation;
}

//-----------------------------------------------------------------------------
//      �|�C���g���C�g��]�����܂�.
//-----------------------------------------------------------------------------
float3 EvaluatePointLight
(
    float3      N,                      // �@���x�N�g��.
    float3      worldPos,               // ���[���h��Ԃ̃I�u�W�F�N�g�ʒu.
    float3      lightPos,               // ���C�g�̈ʒu.
    float       lightInvRadiusSq,       // ���C�g���a��2��̋t��.
    float3      lightColor              // ���C�g�J���[.
)
{
    float3 dif = lightPos - worldPos;
    float3 L = normalize(dif);
    float  att = GetDistanceAttenuation(dif, lightInvRadiusSq);

    return saturate(dot(N, L)) * lightColor * att / (4.0f * F_PI);
}
#endif

//-----------------------------------------------------------------------------
//      �s�N�Z���V�F�[�_�̃��C���G���g���[�|�C���g�ł�.
//-----------------------------------------------------------------------------
PSOutput main(VSOutput input)
{
    PSOutput output = (PSOutput)0;

    float3 L = normalize(LightPosition  - input.WorldPos);
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
#ifndef OPTIMIZATION
    float3 lit  = EvaluatePointLight(N, input.WorldPos, LightPosition, LightColor) * LightIntensity;
#else
    float3 lit  = EvaluatePointLight(N, input.WorldPos, LightPosition, LightInvSqrRadius, LightColor) * LightIntensity;
#endif

    output.Color.rgb = lit * BRDF;
    output.Color.a   = 1.0f;

    return output;
}