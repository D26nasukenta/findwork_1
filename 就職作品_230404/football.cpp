#include <windows.h>

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "manager.h"
#include "model.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "player.h"
#include "goal.h"
#include "title.h"
#include "football.h"
#include "meshfield.h"
#include "ballstate.h"

#define GRAVITY 9.8
#define MINIT  60

void FootBall::Init()
{
	g_Model = new Model();
	g_Model->Load((char*)"asset\\model\\football_001.obj");


	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	Renderer::CreatePixelShader(&m_PixelShaderShadow, "BlackShadowPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.6f, 0.6f, 0.6f);

}

void FootBall::Uninit()
{
	/*m_VertexBuffer->Release();
	m_Texture->Release();*/
	g_Model->Unload();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void FootBall::Update()
{
	Scene* scene = Manager::GetScene();
	FootBall::Physics(scene);


}

void FootBall::Draw()
{

	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);


	g_Model->Draw();

	// �e�s�񐶐�
	D3DXMatrixIdentity(&g_MatrixShadow);


	// �e�s��𐶐�����D3DXMatrixShadow()�֐���DirectX�Ɏ�������Ă���
	D3DXPLANE plane;
	D3DXVECTOR3 pt = { 0, 0.1f, 0 }, nor = { 0, 1, 0 };
	D3DXPlaneFromPointNormal(
		&plane,	// ���ʂ�\��D3DXPLANE�\����
		&pt,	// ���ʏ�̔C�ӂ̓_
		&nor);	// ���ʂ̖@���x�N�g��
	D3DXMatrixShadow(&g_MatrixShadow, &g_light, &plane);

	D3DXMatrixMultiply(&world, &world, &g_MatrixShadow);
	Renderer::SetWorldMatrix(&world);

	Renderer::GetDeviceContext()->PSSetShader(m_PixelShaderShadow, NULL, 0);

	g_Model->Draw();

}

void FootBall::Shoot(float vy, float vz)
{

	m_vy = vy;
	m_vz = vz;
	m_kick = true;


}

void FootBall::CurveShoot(float vx, float vy, float vz)
{
	m_vx = vx;
	m_vy = vy;
	m_vz = vz;
	m_curvekick = true;


}

void FootBall::Pass(float vy, float vz)
{

	m_vy = vy;
	m_vz = vz;
	m_Pass = true;


}

void FootBall::Physics(Scene* scene)
{
	Title* g_Title = nullptr;

	MeshField* meshfield = scene->GetGameObject<MeshField>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);


	if (scene->GetSceneNumber() == 1 || scene->GetSceneNumber() == 2)
	{


		D3DXVECTOR3 Direction = m_Position - player->GetPosition();
		D3DXVECTOR3 GoalDirection = m_Position - goal->GetPosition();

		float Length = D3DXVec3Length(&Direction);
		float GoalLength = D3DXVec3Length(&GoalDirection);


		//�{�[�����V���[�g���ꂽ�Ƃ�
		if (m_kick == true)
		{
			m_DropBall = true;
			m_vz += m_rz;
			m_Position += FootBall::GetForward() * m_vz;

			if (m_vz <= 0.0f)
			{
				m_vz = 0.0f;
				m_kick = false;
			}
		}

		//�R������i�J�[�u�j
		if (m_curvekick == true)
		{
			m_DropBall = true;

			m_vx = m_vx * m_rx;
			m_Position -= FootBall::GetRIGHT() * m_vx;

			m_vz += m_rz;
			m_Position += FootBall::GetForward() * m_vz;

			if (m_vz <= 0.0f)
			{
				m_vz = 0.0f;
				m_curvekick = false;
			}

			if (m_vx > 0.1f)
			{
				m_rx -= (0.5f / 60);
			}
			else
			{
				m_vx = 0.0f;
				m_rx = 1.0f;
			}


		}
		if (m_Pass == true)
		{
			m_vz += m_rz;
			m_Position.z += m_vz;
			if (m_vz <= 0.0f)
			{
				m_Pass = false;
			}
		}

		//�{�[�����h���b�v(�����Ă���)�Ȃ�
		if (m_DropBall == true)
		{
			//�d��
			m_vy += m_ry;
			m_Position += FootBall::GetUP() * m_vy;
		}

		//�n�ʂɃ{�[�������Ă���(���ɑ��x��������)
		if (m_Position.y <= meshfield->GetHeight(m_Position) && m_vy <= -0.3f)
		{
			//���x������������������
			m_vy *= n;

		}

		//�n�ʂɃ{�[�������Ă���(��ɒ��˂�����O��)
		if (m_Position.y <= meshfield->GetHeight(m_Position) && m_vy <= 0.0f)
		{
			m_Position.y = meshfield->GetHeight(m_Position);
			m_vy = 0.0f;
			m_DropBall = false;
		}

	}

	else if (scene->GetSceneNumber() == 3 && player->GetTutorialStep() >= 3)
	{
		D3DXVECTOR3 Direction = m_Position - player->GetPosition();
		D3DXVECTOR3 GoalDirection = m_Position - goal->GetPosition();

		float Length = D3DXVec3Length(&Direction);
		float GoalLength = D3DXVec3Length(&GoalDirection);


		//�{�[�����V���[�g���ꂽ�Ƃ�
		if (m_kick == true)
		{
			m_DropBall = true;
			m_vz += m_rz;
			m_Position += FootBall::GetForward() * m_vz;

			if (m_vz <= 0.0f)
			{
				m_vz = 0.0f;
				m_kick = false;
			}
		}

		//�R������i�J�[�u�j
		if (m_curvekick == true)
		{
			m_DropBall = true;

			m_vx = m_vx * m_rx;
			m_Position -= FootBall::GetRIGHT() * m_vx;

			m_vz += m_rz;
			m_Position += FootBall::GetForward() * m_vz;

			if (m_vz <= 0.0f)
			{
				m_vz = 0.0f;
				m_curvekick = false;
			}

			if (m_vx > 0.1f)
			{
				m_rx -= (0.5f / 60);
			}
			else
			{
				m_vx = 0.0f;
				m_rx = 1.0f;
			}


		}
		if (m_Pass == true)
		{
			m_vz += m_rz;
			m_Position.z += m_vz;
			if (m_vz <= 0.0f)
			{
				m_Pass = false;
			}
		}

		//�{�[�����h���b�v(�����Ă���)�Ȃ�
		if (m_DropBall == true)
		{
			//�d��
			m_vy += m_ry;
			m_Position += FootBall::GetUP() * m_vy;
		}

		//�n�ʂɃ{�[�������Ă���(���ɑ��x��������)
		if (m_Position.y <= meshfield->GetHeight(m_Position) && m_vy <= -0.3f)
		{
			//���x������������������
			m_vy *= n;

		}

		//�n�ʂɃ{�[�������Ă���(��ɒ��˂�����O��)
		if (m_Position.y <= meshfield->GetHeight(m_Position) && m_vy <= 0.0f)
		{
			m_Position.y = meshfield->GetHeight(m_Position);
			m_vy = 0.0f;
			m_DropBall = false;
		}
	}

}

