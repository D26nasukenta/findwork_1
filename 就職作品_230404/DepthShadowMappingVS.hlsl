#include "common.hlsl"
void main(in VS_IN In, out PS_IN Out)
{
//���[���h�r���[�v���W�F�N�V�����s��쐬
    matrix wvp; //�����̏�������View��Projection�ɂ�
    wvp = mul(World,View); //1�p�X�ڂ̓��C�g�J�����̍s���
    wvp = mul(wvp,Projection); //2�p�X�ڂ͒ʏ�J�����̍s�񂪐ݒ肳���
    
    
    float4 worldNormal, normal; //�@���̃��[���h�ϊ�
    normal = float4(In.Normal.xyz, 0.0); //�@���x�N�g����w��0�Ƃ��ăR�s�[�i���s�ړ����Ȃ�����)
    worldNormal = mul(normal, World); //�@�������[���h�s��ŉ�]����
    worldNormal = normalize(worldNormal);
   
//��������
    float light = -dot(Light.Direction.xyz, worldNormal.xyz);
    light = saturate(light);
    Out.Diffuse = light;
    Out.Diffuse.a = In.Diffuse.a;
    Out.Position = mul(In.Position, wvp); //���_���W�����[���h�ϊ����ďo��
    Out.Normal = worldNormal; //�@�����o��
    Out.TexCoord = In.TexCoord; //�e�N�X�`�����W���o��

//���C�g�̍s����g���Ē��_��ϊ����ďo�͂���
    matrix lightwvp;
    lightwvp = mul(World, Light.View); //���[���h�s�񁖃��C�g�r���[�s��
    lightwvp = mul(lightwvp , Light.Projection); //����Ɂ����C�g�v���W�F�N�V�����s��
    Out.ShadowPosition = mul(In.Position, lightwvp); //���C�g���猩�����_���W�o��
}
