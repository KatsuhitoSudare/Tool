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
    float3      LightPosition       : packoffset(c0);
    float       LightAngleOffset    : packoffset(c0.w);
    float3      LightColor          : packoffset(c1);
    float       LightIntensity      : packoffset(c1.w);
    float3      LightForward        : packoffset(c2);
    float       LightAngleScale     : packoffset(c2.w);
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
SamplerState    IESSmp       : register(s0);
Texture2D       IESMap       : register(t0);

Texture2D       BaseColorMap : register(t1);
SamplerState    BaseColorSmp : register(s1);

Texture2D       MetallicMap  : register(t2);
SamplerState    MetallicSmp  : register(s2);

Texture2D       RoughnessMap : register(t3);
SamplerState    RoughnessSmp : register(s3);

Texture2D       NormalMap    : register(t4);
SamplerState    NormalSmp    : register(s4);


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
    attenuation *= SmoothDistanceAttenuation(sqrDist, invSqrAttRadius);

    return attenuation;
}

//-----------------------------------------------------------------------------
//      �p�x���������߂܂�.
//-----------------------------------------------------------------------------
float GetAngleAttenuation
(
    float3  unnormalizedLightVector,    // ���C�g�ʒu�ƃI�u�W�F�N�g�ʒu�̍����x�N�g��.
    float3  lightDir,                   // ���K���ς݂̃��C�g�x�N�g��.
    float   lightAngleScale,            // �X�|�b�g���C�g�̊p�x�����X�P�[��.
    float   lightAngleOffset            // �X�|�b�g���C�g�̊p�x�I�t�Z�b�g.
)
{
    // CPU���Ŏ��̒l���v�Z���Ă���.
    // float lightAngleScale = 1.0f / max(0.001f, (cosInner - cosOuter));
    // float lightAngleOffset  = -cosOuter * lightAngleScale;
    // ��L�ɂ�����
    // * cosInner�͓��p�̗]��.
    // * cosOuter�͊O�p�̗]��.
    // �Ƃ��܂�.

    float cd = dot(lightDir, unnormalizedLightVector);
    float attenuation = saturate(cd * lightAngleScale + lightAngleOffset);

    // ���炩�ɕω�������.
    attenuation *= attenuation;

    return attenuation;
}

//-----------------------------------------------------------------------------
//      IES�v���t�@�C���ɂ�錸�������߂܂�.
//-----------------------------------------------------------------------------
float GetIESProfileAttenuation(float3 lightDir, float3 lightForward)
{
    // �p�x�����߂�.
    float  thetaCoord   = dot(lightDir, lightForward) * 0.5f + 0.5f;
    float  tangentAngle = atan2(lightDir.y, lightDir.x);
    float  phiCoord     = (tangentAngle / F_PI) * 0.5f + 0.5;
    float2 texCoord     = float2(thetaCoord, phiCoord);

    // IES�e�N�X�`�����琳�K�����ꂽ���x�����o��.
    return IESMap.SampleLevel(IESSmp, texCoord, 0).r;
}

//-----------------------------------------------------------------------------
//      �t�H�g���g���b�N���C�g��]�����܂�.
//-----------------------------------------------------------------------------
float3 EvaluatePhotometricLight
(
    float3      N,                  // �@���x�N�g��.
    float3      worldPos,           // ���[���h��Ԃ̃I�u�W�F�N�g�ʒu.
    float3      lightPos,           // ���C�g�ʒu.
    float3      lightForward,       // ���C�g�̏Ǝ˕���.
    float3      lightColor,         // ���C�g�J���[.
    float       lightAngleScale,    // ���C�g�̊p�x�X�P�[��.
    float       lightAngleOffset    // ���C�g�̊p�x�I�t�Z�b�g.
)
{
    float3 unnormalizedLightVector = (lightPos - worldPos);
    float3 L = normalize(unnormalizedLightVector);
    float att = 1.0f;
    att *= GetAngleAttenuation(-L, lightForward, lightAngleScale, lightAngleOffset);
    att *= GetIESProfileAttenuation(L, lightForward);

    return saturate(dot(N, L)) * lightColor * att / (4.0f * F_PI);
}

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
    float3 lit  = EvaluatePhotometricLight(
        N,
        input.WorldPos,
        LightPosition,
        LightForward,
        LightColor,
        LightAngleScale,
        LightAngleOffset) * LightIntensity;

    output.Color.rgb = lit * BRDF;
    output.Color.a   = 1.0f;

    return output;
}