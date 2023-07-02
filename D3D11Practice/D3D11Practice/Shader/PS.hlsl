struct PixelInputType
{
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float4 position : SV_POSITION;
    float3 worldPos : TEXCOORD1;
};

// �f�B���N�V�������C�g�p�̃f�[�^���󂯎�邽�߂̒萔�o�b�t�@�[��p�ӂ���
cbuffer DirectionLightCb : register(b1)
{
    float3 ligDirection; //���C�g�̕���
    float3 ligColor; //���C�g�̃J���[

    // step-3 ���_�̃f�[�^�ɃA�N�Z�X���邽�߂̕ϐ���萔�o�b�t�@�[�ɒǉ�����
    float3 eyePos; //���_�̈ʒu
};

///////////////////////////////////////////
// �V�F�[�_�[���\�[�X
///////////////////////////////////////////
// ���f���e�N�X�`��
Texture2D<float4> g_texture : register(t0);

///////////////////////////////////////////
// �T���v���[�X�e�[�g
///////////////////////////////////////////
sampler g_sampler : register(s0);


float4 main(PixelInputType input) : SV_TARGET
{
     // �s�N�Z���̖@���ƃ��C�g�̕����̓��ς��v�Z����
    float t = dot(input.normal, ligDirection);
    t *= -1.0f;
  
    // ���ς̌��ʂ�0�ȉ��Ȃ�0�ɂ���
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    
    // �g�U���ˌ������߂�
    float3 diffuseLig = ligColor * t;

    // step-4 ���˃x�N�g�������߂�
    float3 refVec = reflect(ligDirection, input.normal);

    // step-5 �������������T�[�t�F�C�X���王�_�ɐL�т�x�N�g�������߂�
    float3 toEye = eyePos - input.worldPos;
    toEye = normalize(toEye);

    // step-6 ���ʔ��˂̋��������߂�
    t = dot(refVec, toEye);
    if (t < 0.0f)
    {
        t = 0.0f;
    }

    // step-7 ���ʔ��˂̋������i��
    t = pow(t, 5.0f);

    // step-8 ���ʔ��ˌ������߂�
    float3 specularLig = ligColor * t;

    // step-9 �g�U���ˌ��Ƌ��ʔ��ˌ��𑫂��Z���āA�ŏI�I�Ȍ������߂�
    float3 lig = diffuseLig + specularLig;
    float4 finalColor = g_texture.Sample(g_sampler, input.tex);

    // step-10 �e�N�X�`���J���[�ɋ��߂�������Z���čŏI�o�̓J���[�����߂�
    finalColor.xyz *= lig;

    return finalColor;
}