#include "common.hlsl"
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

	float4 normal = normalize(In.Normal); //�s�N�Z���̖@���𐳋K��
	float light = 0.5 - dot(normal.xyz, Light.Direction.xyz) * 0.5; //�����v�Z������

	//�X�y�L�����v�Z
	//�J��������s�N�Z���֌������x�N�g��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //���K������

	//���̔��˃x�N�g�����v�Z
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //���K������

	float specular = -dot(eyev, refv); //���ʔ��˂̌v�Z
	specular = saturate(specular); //�l���T�`�����[�g

	

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= In.Diffuse.rgb * light ; //���邳����Z
	outDiffuse.a *= In.Diffuse.a; //���ɖ��邳�͊֌W�Ȃ��̂ŕʌv�Z
	specular = pow(specular, 50); //�����ł͂R�O�悵�Ă�

	outDiffuse.rgb += specular;//�X�y�L�����l���f�t���[�Y�Ƃ��đ�������
}