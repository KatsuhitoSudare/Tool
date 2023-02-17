//-----------------------------------------------------------------------------
// File : PhongPS.hlsl
// Desc : Phong Lighting Pixel Shader.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

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
    float3 Diffuse      : packoffset( c0 );     // �g�U���˗��ł�.
    float  Alpha        : packoffset( c0.w );   // ���ߓx�ł�.
    float3 Specular     : packoffset( c1 );     // ���ʔ��˗��ł�.
    float  Shininess    : packoffset( c1.w );   // ���ʔ��ˋ��x�ł�.
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

    float3 R = normalize(-reflect(V, N));

    float4 color    = ColorMap.Sample( WrapSmp, input.TexCoord );
    float3 diffuse  = LightColor * Diffuse  * saturate(dot( L, N ));
    float3 specular = LightColor * Specular * pow( saturate(dot(L, R)), Shininess );

    output.Color = float4( color.rgb * ( diffuse + specular ), color.a * Alpha );
    return output;
}