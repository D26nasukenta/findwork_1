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
	//�ړ�����
	MoveEffect();

	//������
	ParticleVectorDecrease(0.98f);

	//�������Ԃ𒴂�����
	UseTimeOverLife();

	//�������Ԃ̉Z
	IncleaseUsetime();

	//�d�͏���
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
