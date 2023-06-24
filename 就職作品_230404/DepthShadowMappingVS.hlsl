#include "common.hlsl"
void main(in VS_IN In, out PS_IN Out)
{
//ワールドビュープロジェクション行列作成
    matrix wvp; //いつもの処理だがViewとProjectionには
    wvp = mul(World,View); //1パス目はライトカメラの行列で
    wvp = mul(wvp,Projection); //2パス目は通常カメラの行列が設定される
    
    
    float4 worldNormal, normal; //法線のワールド変換
    normal = float4(In.Normal.xyz, 0.0); //法線ベクトルのwを0としてコピー（平行移動しないため)
    worldNormal = mul(normal, World); //法線をワールド行列で回転する
    worldNormal = normalize(worldNormal);
   
//光源処理
    float light = -dot(Light.Direction.xyz, worldNormal.xyz);
    light = saturate(light);
    Out.Diffuse = light;
    Out.Diffuse.a = In.Diffuse.a;
    Out.Position = mul(In.Position, wvp); //頂点座標をワールド変換して出力
    Out.Normal = worldNormal; //法線を出力
    Out.TexCoord = In.TexCoord; //テクスチャ座標を出力

//ライトの行列を使って頂点を変換して出力する
    matrix lightwvp;
    lightwvp = mul(World, Light.View); //ワールド行列＊ライトビュー行列
    lightwvp = mul(lightwvp , Light.Projection); //さらに＊ライトプロジェクション行列
    Out.ShadowPosition = mul(In.Position, lightwvp); //ライトから見た頂点座標出力
}
