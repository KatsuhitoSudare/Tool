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
    int4 boneIndices : BONEINDICES;
    float4 boneWeights : BONEWEIGHTS;
};

struct PixelInputType
{
    float2 tex : TEXCOORD0;
    float4 normal : NORMAL;
    float4 position : SV_POSITION;
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;

    //// ���_�ʒu�Ɩ@���̏����l
    //float4 localPosition = float4(0.0, 0.0, 0.0, 0.0);
    //float4 localNormal = float4(0.0, 0.0, 0.0, 0.0);

    //// �X�L�j���O����
    //for (int i = 0; i < 4; ++i)
    //{
    //    float weight = input.boneWeights[i];
    //    if (weight > 0.0)
    //    {
    //        int boneIndex = input.boneIndices[i];
    //        matrix boneTransform = boneTransforms[boneIndex];
    //        float4 skinnedPosition = mul(float4(input.position, 1.0), boneTransform);
    //        float4 skinnedNormal = mul(float4(input.normal, 0.0), boneTransform);

    //        localPosition += skinnedPosition * weight;
    //        localNormal += skinnedNormal * weight;
    //    }
    //}

    // ���[���h���W�n�ւ̕ϊ�
    output.position = mul(float4(input.position, 1.0),world);

    // �@�������[���h���W�n�ɕϊ�
    output.normal = mul(float4(input.normal,1.0), world);

    // �e�N�X�`�����W�̐ݒ�
    output.tex = input.tex;

    // �r���[���W�n�ւ̕ϊ�
    output.position = mul(output.position, view);

    // �N���b�v���W�n�ւ̕ϊ�
    output.position = mul(output.position, projection);

    return output;
}
