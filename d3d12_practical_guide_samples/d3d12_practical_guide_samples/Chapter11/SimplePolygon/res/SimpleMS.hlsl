//-----------------------------------------------------------------------------
// File : SimpleMS.hlsl
// Desc : Simple Mesh Shader.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// MSInput structure
///////////////////////////////////////////////////////////////////////////////
struct MSInput
{
    float3 Position;    // �ʒu���W�ł�.
    float4 Color;       // ���_�J���[�ł�.
};

///////////////////////////////////////////////////////////////////////////////
// MSOutput structure
///////////////////////////////////////////////////////////////////////////////
struct MSOutput
{
    float4 Position : SV_POSITION;  // �ʒu���W�ł�.
    float4 Color    : COLOR;        // ���_�J���[�ł�.
};

///////////////////////////////////////////////////////////////////////////////
// TransformParam structure
///////////////////////////////////////////////////////////////////////////////
struct TransformParam
{
    float4x4 World;     // ���[���h�s��ł�.
    float4x4 View;      // �r���[�s��ł�.
    float4x4 Proj;      // �ˉe�s��ł�.
};

//-----------------------------------------------------------------------------
// Resources
//-----------------------------------------------------------------------------
StructuredBuffer<MSInput>       Vertices    : register(t0);
StructuredBuffer<uint3>         Indices     : register(t1);
ConstantBuffer<TransformParam>  Transform   : register(b0);

//-----------------------------------------------------------------------------
//      ���b�V���V�F�[�_�̃G���g���[�|�C���g�ł�.
//-----------------------------------------------------------------------------
[numthreads(64, 1, 1)]
[outputtopology("triangle")]
void main
(
    uint groupIndex : SV_GroupIndex,
    out vertices MSOutput verts[3],
    out indices  uint3    tris[1]
)
{
    // �X���b�h�O���[�v�̒��_�ƃv���~�e�B�u�̐���ݒ�.
    SetMeshOutputCounts(3, 1);

    // ���_�ԍ���ݒ�.
    if (groupIndex < 1)
    {
        tris[groupIndex] = Indices[groupIndex];
    }

    // ���_�f�[�^��ݒ�.
    if (groupIndex < 3)
    {
        MSOutput output = (MSOutput)0;

        float4 localPos = float4(Vertices[groupIndex].Position, 1.0f);
        float4 worldPos = mul(Transform.World, localPos);
        float4 viewPos  = mul(Transform.View,  worldPos);
        float4 projPos  = mul(Transform.Proj,  viewPos);

        output.Position = projPos;
        output.Color    = Vertices[groupIndex].Color;

        verts[groupIndex] = output;
    }
}