//=============================================================================
//
// スプライト処理 [sprite.cpp]
// Author : 渡辺拓海
//
//=============================================================================
#include "sprite.h"
#include "renderer.h"
#include "texture.h"
#include "Scene.h"
#include "Camera.h"
#include "manager.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VERTEX 4	//必要な頂点の数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;	// 頂点情報
static ID3D11InputLayout* m_VertexLayout = NULL;
static ID3D11VertexShader* m_VertexShader = NULL;
static ID3D11PixelShader* m_PixelShader = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
void Sprite::InitSprite()
{
	ID3D11Device* pDevice = Renderer::GetDevice();

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);

}

//=============================================================================
// 終了処理
//=============================================================================
void Sprite::UninitSprite()
{
	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// スプライトデータ設定
// 座標・サイズ・UV指定・頂点色
//=============================================================================
void Sprite::DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点０番（左上の頂点）
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// 頂点１番（右上の頂点）
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// 頂点２番（左下の頂点）
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// 頂点３番（右下の頂点）
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(texNo));

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// スプライトデータ設定
// 座標・サイズ・UV指定・頂点色・回転角度
//=============================================================================
void Sprite::DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXVECTOR4 Color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	float BaseAngle = atan2f(hh, hw);		// 中心点から頂点に対する角度
	D3DXVECTOR2 temp = D3DXVECTOR2(hw, hh);
	float Radius = D3DXVec2Length(&temp);	// 中心点から頂点に対する距離

	float x = X - cosf(BaseAngle + Rot) * Radius;
	float y = Y - sinf(BaseAngle + Rot) * Radius;
	vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X + cosf(BaseAngle - Rot) * Radius;
	y = Y - sinf(BaseAngle - Rot) * Radius;
	vertex[1].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X - cosf(BaseAngle - Rot) * Radius;
	y = Y + sinf(BaseAngle - Rot) * Radius;
	vertex[2].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X + cosf(BaseAngle + Rot) * Radius;
	y = Y + sinf(BaseAngle + Rot) * Radius;
	vertex[3].Position = D3DXVECTOR3(x, y, 0.0f);

	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	//法線を設定
	vertex[0].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//UVの設定
	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	//マトリクスの設定
	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(texNo));

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

void Sprite::DrawSpriteBillBoard(int texNo, D3DXVECTOR3 Position,D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale,float U, float V, float UW, float VH, D3DXVECTOR4 Color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(-1.0f,  1.0f, 0.0f);
	vertex[1].Position = D3DXVECTOR3( 1.0f,  1.0f, 0.0f);
	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[3].Position = D3DXVECTOR3( 1.0f, -1.0f, 0.0f);

	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	//法線を設定
	vertex[0].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//UVの設定
	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	//　カメラのビューマトリクス取得
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);
	D3DXMATRIX view = camera->GetViewMatrix();

	//　ビューの逆行列
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);//逆行列
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	//ワールドマトリクス設定
	D3DXMATRIX world, scale ,rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);

	world = scale * rot* invView * trans;
	Renderer::SetWorldMatrix(&world);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(texNo));

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// スプライトデータ設定（左上指定）
// 座標・サイズ・UV指定
//=============================================================================
void Sprite::DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 左上を原点として設定するプログラム
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(10.0f, 10.0f, 10.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(10.0f, 10.0f, 10.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(10.0f, 10.0f, 10.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(10.0f, 10.0f, 10.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(texNo));

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(NUM_VERTEX, 0);
}
