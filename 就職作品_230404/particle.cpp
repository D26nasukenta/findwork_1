#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "particle.h"

void Particle::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);


	vertex[2].Position = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);


	vertex[3].Position = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};//<-������[���N���A����B(�\���̓������ׂă[����)
	//�\���̓������ׂă[���ɂ���B
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;//�f�t�H���g�@->�@�_�C�i�~�b�N
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//0 -> D3D11_CPU_ACCESS_WRITE
	//�d���Ȃ邩��ύX����̂͐T�d��
	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;


	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\particle.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\particle_square.png",
		NULL,
		NULL,
		&m_Texture2,
		NULL);


	assert(m_Texture2);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\particle_tri.png",
		NULL,
		NULL,
		&m_Texture3,
		NULL);


	assert(m_Texture3);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");



}

void Particle::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();
	m_Texture2->Release();
	m_Texture3->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Particle::Update()
{

	CreateParticle(D3DXVECTOR3 (SCREEN_WIDTH /2, SCREEN_HEIGHT - 30.0f, 0.0f), D3DXVECTOR3(rand() % 200 -100.0f,-(rand() % 10 + 20.0f),0.0f) ,
					D3DXVECTOR3 (0.0f,0.9f,0.0f), D3DXVECTOR3 (3.0f,3.0f,00.0f),
					D3DXVECTOR4 (1.0f,0.0f,0.0f,1.0f), 60, rand() % 3);


	// �p�[�e�B�N���X�V
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		// �g�p��
		if (g_Particle[i].status)
		{
			g_Particle[i].vel += g_Particle[i].acc;
			g_Particle[i].pos += g_Particle[i].vel;

			// ��ʊO�ɏo�������
			if (g_Particle[i].pos.x < -SCREEN_WIDTH  ||
				g_Particle[i].pos.x >  SCREEN_WIDTH  ||
				g_Particle[i].pos.y < -SCREEN_HEIGHT  ||
				g_Particle[i].pos.y >  SCREEN_HEIGHT )
			{
				g_Particle[i].status = 0;
			}

			// ���Ŏ��Ԃ��o�߂��������
			if (g_Particle[i].life && --g_Particle[i].life <= 0)
			{
				g_Particle[i].life = 0;
				g_Particle[i].status = 0;
			}
		}
	}
}

void Particle::Draw()
{
	{

		for (int i = 0; i < PARTICLE_MAX; i++)
		{
			if (g_Particle[i].status)
			{
				g_Particle[i].col = D3DXVECTOR4( 0.1f* (rand()%10), 0.1f * (rand() % 10), 0.1f * (rand() % 10),0.8f);
				//���_�f�[�^��������
				D3D11_MAPPED_SUBRESOURCE msr;
				//�}�b�v�֐��Œ��_�̒��g�̏�����������
				Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

				VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

				vertex[0].Position = D3DXVECTOR3(0.0f * g_Particle[i].size.x, 0.0f * g_Particle[i].size.y, 0.0f) + g_Particle[i].pos;
				vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				vertex[0].Diffuse = g_Particle[i].col;
				vertex[0].TexCoord = D3DXVECTOR2(0, 0);

				vertex[1].Position = D3DXVECTOR3(10.0f * g_Particle[i].size.x, 0.0f *g_Particle[i].size.y, 0.0f) + g_Particle[i].pos;
				vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				vertex[1].Diffuse = g_Particle[i].col;
				vertex[1].TexCoord = D3DXVECTOR2(1, 0);

				vertex[2].Position = D3DXVECTOR3(0.0f  *g_Particle[i].size.x, 10.0f * g_Particle[i].size.y, 0.0f) + g_Particle[i].pos;
				vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				vertex[2].Diffuse = g_Particle[i].col;
				vertex[2].TexCoord = D3DXVECTOR2(0, 1);

				vertex[3].Position = D3DXVECTOR3(10.0f * g_Particle[i].size.x, 10.0f * g_Particle[i].size.y, 0.0f) + g_Particle[i].pos;
				vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				vertex[3].Diffuse = g_Particle[i].col;
				vertex[3].TexCoord = D3DXVECTOR2(1, 1);

				Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
			}
			//���̓��C�A�E�g�ݒ�
			Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

			//�V�F�[�_�ݒ�
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
			
			
			//�}�g���N�X�ݒ�
			Renderer::SetWorldViewProjection2D();


			//���_�o�b�t�@�ݒ�
			UINT stride = sizeof(VERTEX_3D);
			UINT offset = 0;
			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

			//�}�e���A���ݒ�
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Renderer::SetMaterial(material);


			//�e�N�X�`���ݒ�
			if (g_Particle[i].texturerandom == 0)
			{
				Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			}
			else if (g_Particle[i].texturerandom == 1)
			{

				Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture2);
			}
			else
			{
				Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture3);

			}

			//�v���~�e�B�u�ݒ�
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			//�|���S���`��

			Renderer::GetDeviceContext()->Draw(4, 0);
			}
		}


}

void Particle::CreateParticle(	D3DXVECTOR3 position, D3DXVECTOR3 velocity,
								D3DXVECTOR3 accel, D3DXVECTOR3 size, 
								D3DXVECTOR4 col, int life, int texturerandom )
{
	
	// �I�u�W�F�N�g�v�[�����疢�g�p������
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!g_Particle[i].status)
		{
			g_Particle[i].pos = position;
			g_Particle[i].vel = velocity;
			g_Particle[i].acc = accel;
			g_Particle[i].size = size;
			g_Particle[i].col = col;
			g_Particle[i].life = life;
			g_Particle[i].texturerandom = texturerandom;
			g_Particle[i].random = true;

			// ��Ԃ��g�p����
			g_Particle[i].status = 1;
			break;
		}
	}
}

