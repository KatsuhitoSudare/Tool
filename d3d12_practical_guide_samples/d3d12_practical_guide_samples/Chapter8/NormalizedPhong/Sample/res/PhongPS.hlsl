//-----------------------------------------------------------------------------
// File : PhongPS.hlsl
// Desc : Phong Lighting Pixel Shader.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Constant Values
//-----------------------------------------------------------------------------
static const float F_PI = 3.141596535f;

///////////////////////////////////////////////////////////////////////////////
// VSOutput structure
///////////////////////////////////////////////////////////////////////////////
struct VSOutput
{   
    float4  Position : SV_POSITION;     // �ʒu���W�ł�.
    float2  TexCoord : TEXCOORD;        // �e�N�X�`�����W�ł�.
    float3  Normal   : NORMAL;          // �@���x�N�g���ł�.
    float3  WorldPos : WORLD_POS;       // ���[���h��Ԃ̈ʒu���W�ł�.
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
cbuffer LightBuffer : register( b1 )
{
    float3 LightPosition  : packoffset( c0 );   // ���C�g�ʒu�ł�.
    float3 LightColor     : packoffset( c1 );   // ���C�g�J���[�ł�.
    float3 CameraPosition : packoffset( c2 );   // �J�����ʒu�ł�.
};

///////////////////////////////////////////////////////////////////////////////
// MaterialBuffer
///////////////////////////////////////////////////////////////////////////////
cbuffer MaterialBuffer : register( b2 )
{
    float3 BaseColor : packoffset( c0 );     // ��{�F�ł�.
    float  Alpha     : packoffset( c0.w );   // ���ߓx�ł�.
    float  Metallic  : packoffset( c1 );     // �����x�ł�.
    float  Shininess : packoffset( c1.y );   // ���ʔ��ˋ��x�ł�.
};

//-----------------------------------------------------------------------------
// Textures and Samplers
//-----------------------------------------------------------------------------
SamplerState WrapSmp  : register( s0 );
Texture2D    ColorMap : register( t0 );

//-----------------------------------------------------------------------------
//      �s�N�Z���V�F�[�_�̃��C���G���g���[�|�C���g�ł�.
//-----------------------------------------------------------------------------
PSOutput main(VSOutput input)
{
    PSOutput output = (PSOutput)0;

    float3 N = normalize(input.Normal);
    float3 L = normalize(LightPosition  - input.WorldPos);
    float3 V = normalize(CameraPosition - input.WorldPos);
    float3 R = normalize(-V + 2.0f * dot(N, V) * N);

    float NL = saturate(dot(N, L));
    float LR = saturate(dot(L, R));

    float4 color    = ColorMap.Sample( WrapSmp, input.TexCoord );
    float3 diffuse  = BaseColor * (1.0f - Metallic)  * (1.0 / F_PI) ;
    float3 specular = BaseColor * Metallic * ((Shininess + 2.0) / (2.0 * F_PI)) * pow( LR, Shininess );

    output.Color = float4( LightColor * color.rgb * ( diffuse + specular ) * NL, color.a * Alpha );
    return output;
}
