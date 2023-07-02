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
    
    output.position = mul(world, float4(input.position, 0.0f)); // ���f���̒��_�����[���h���W�n�ɕϊ�
    output.worldPos = input.position;
    output.position = mul(view, output.position); // ���[���h���W�n����J�������W�n�ɕϊ�
    output.position = mul(projection, output.position); // �J�������W�n����X�N���[�����W�n�ɕϊ�

    // ���_�@�����s�N�Z���V�F�[�_�[�ɓn��
    output.normal = mul(world, float4(input.normal,0.0f)); // �@������]������
    output.tex = input.tex;

    return output;
}
