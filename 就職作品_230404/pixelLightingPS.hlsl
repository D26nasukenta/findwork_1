#include "common.hlsl"
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

	float4 normal = normalize(In.Normal); //ピクセルの法線を正規化
	float light = 0.5 - dot(normal.xyz, Light.Direction.xyz) * 0.5; //光源計算をする

	//スペキュラ計算
	//カメラからピクセルへ向かうベクトル
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //正規化する

	//光の反射ベクトルを計算
	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv); //正規化する

	float specular = -dot(eyev, refv); //鏡面反射の計算
	specular = saturate(specular); //値をサチュレート

	

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= In.Diffuse.rgb * light ; //明るさを乗算
	outDiffuse.a *= In.Diffuse.a; //αに明るさは関係ないので別計算
	specular = pow(specular, 50); //ここでは３０乗してみ

	outDiffuse.rgb += specular;//スペキュラ値をデフューズとして足しこむ
}