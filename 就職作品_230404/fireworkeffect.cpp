#include"sprite.h"
#include"texture.h" 
#include "fireworkeffect.h"

void FireWorkEffect::Init()
{
	m_Texture = Texture::LoadTexture("asset\\texture\\fire.png");

}

void FireWorkEffect::Uninit()
{
}

void FireWorkEffect::Update()
{
	//移動処理
	MoveEffect();

	//減衰率
	ParticleVectorDecrease(0.98f);

	//生存時間を超えた時
	UseTimeOverLife();

	//生存時間の可算
	IncleaseUsetime();

	//重力処理
	ParticleGravity();

}

void FireWorkEffect::Draw()
{

	Renderer::GetDeviceContext()->PSSetShaderResources(0,1,Texture::GetTexture(m_Texture));

	D3DXVECTOR4 Color = D3DXVECTOR4(1, 1, 1, 1);

	Sprite::DrawSpriteBillBoard(
		m_Texture,
		m_Position,
		m_Rotation,
		m_Scale,
		0,
		0,
		1,
		1,
		Color,
		0
		);

}
