//-----------------------------------------------------------------------------
// File : BasicMS.hlsl
// Desc : Vertex Shader.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// MSInput structure
///////////////////////////////////////////////////////////////////////////////
struct MSInput
{
    float3  Position;  // �ʒu���W�ł�.
    float3  Normal;    // �@���x�N�g���ł�.
    float2  TexCoord;  // �e�N�X�`�����W�ł�.
    float3  Tangent;   // �ڐ��x�N�g���ł�.
};

///////////////////////////////////////////////////////////////////////////////
// MSOutput structure
///////////////////////////////////////////////////////////////////////////////
struct MSOutput
{
    float4      Position        : SV_POSITION;  // �ʒu���W�ł�.
    float2      TexCoord        : TEXCOORD;     // �e�N�X�`�����W�ł�.
    float3      WorldPos        : WORLD_POS;    // ���[���h��Ԃ̈ʒu���W�ł�.
    float3      Tangent         : TANGENT;      // �ڐ��x�N�g���ł�.
    float3      Bitangent       : BITANGENT;    // �]�ڐ��x�N�g���ł�.
    float3      Normal          : NORMAL;       // �@���x�N�g���ł�.
};

///////////////////////////////////////////////////////////////////////////////
// Transform structure
///////////////////////////////////////////////////////////////////////////////
struct TransformParam
{
    float4x4 View;  // �r���[�s��ł�.
    float4x4 Proj;  // �ˉe�s��ł�.
};

///////////////////////////////////////////////////////////////////////////////
// MeshParam structure
///////////////////////////////////////////////////////////////////////////////
struct MeshParam
{
    float4x4 World; // ���[���h�s��ł�.
};

///////////////////////////////////////////////////////////////////////////////
// Meshlet structure
///////////////////////////////////////////////////////////////////////////////
struct Meshlet
{
    uint VertexOffset;      // ���_�ԍ��I�t�Z�b�g.
    uint VertexCount;       // �o�͒��_��.
    uint PrimitiveOffset;   // �v���~�e�B�u�ԍ��I�t�Z�b�g.
    uint PrimitiveCount;    // �o�̓v���~�e�B�u��.
};

//-----------------------------------------------------------------------------
// Resources
//-----------------------------------------------------------------------------
ConstantBuffer<TransformParam> CbTransform  : register(b0);
ConstantBuffer<MeshParam>      CbMesh       : register(b1);
StructuredBuffer<MSInput>      Vertices     : register(t0);
StructuredBuffer<uint>         Indices      : register(t1);
StructuredBuffer<Meshlet>      Meshlets     : register(t2);
StructuredBuffer<uint>         Primitives   : register(t3);


//------------------------------------------------------------------------------
//      �p�b�L���O���ꂽ�C���f�b�N�X�f�[�^��W�J����.
//------------------------------------------------------------------------------
uint3 UnpackPrimitiveIndex(uint packedIndex)
{
    return uint3(
        packedIndex & 0x3FF,
        (packedIndex >> 10) & 0x3FF,
        (packedIndex >> 20) & 0x3FF);
}

//-----------------------------------------------------------------------------
//      ���C���G���g���[�|�C���g�ł�.
//-----------------------------------------------------------------------------
[numthreads(128, 1, 1)]
[outputtopology("triangle")]
void main
(
    uint groupThreadId  : SV_GroupThreadID,
    uint groupId        : SV_GroupID,
    out vertices MSOutput   verts[64],
    out indices  uint3      polys[126]
)
{
    Meshlet m = Meshlets[groupId];

    SetMeshOutputCounts(m.VertexCount, m.PrimitiveCount);

    if (groupThreadId < m.PrimitiveCount)
    {
        uint packedIndex     = Primitives[m.PrimitiveOffset + groupThreadId];
        polys[groupThreadId] = UnpackPrimitiveIndex(packedIndex);
    }
    
    if (groupThreadId < m.VertexCount)
    {
        uint     index  = Indices[m.VertexOffset + groupThreadId];
        MSInput  input  = Vertices[index];
        MSOutput output = (MSOutput)0;

        float4 localPos = float4(input.Position, 1.0f);
        float4 worldPos = mul(CbMesh.World,     localPos);
        float4 viewPos  = mul(CbTransform.View, worldPos);
        float4 projPos  = mul(CbTransform.Proj, viewPos);

        output.Position = projPos;
        output.TexCoord = input.TexCoord;
        output.WorldPos = worldPos.xyz;

        // ���x�N�g��.
        float3 N = normalize(mul((float3x3)CbMesh.World, input.Normal));
        float3 T = normalize(mul((float3x3)CbMesh.World, input.Tangent));
        float3 B = normalize(cross(N, T));

        output.Tangent      = T;
        output.Bitangent    = B;
        output.Normal       = N;

        verts[groupThreadId] = output;
    }
}