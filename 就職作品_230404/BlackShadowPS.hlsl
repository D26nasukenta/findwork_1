#include "common.hlsl"

Texture2D g_Texture : register(t0); //�ʏ�e�N�X�`��
Texture2D g_TextureShadowDepth : register(t1); //�V���h�E�}�b�v
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

    outDiffuse.rgb = 0.0f;
    outDiffuse.a = 0.6f;
}