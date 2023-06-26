#include <math.h>
#include"main.h"
#include "AnimationModel.h"
#include "camera.h"
#include"renderer.h"
#include "player.h"
#include "input.h"
#include "scene.h"
#include "audio.h"
#include "football.h"
#include "transition.h"
#include "goal.h"
#include "gaugered.h"
#include "gaugeback.h"
#include "meshfield.h"
#include "controlui.h"
#include "Command.h"
#include "InputHudler.h"

bool key = false;
void PLAYER::Init()
{
	m_Model = new AnimationModel();
	m_Model->Load((char*)"asset\\model\\Akai_Run.fbx");//Akai_Idle,Akai_Run

	//�V�����A�j���[�V�����̃��[�h
	m_Model->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");

	m_AnimationName = "Idle";
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	Renderer::CreatePixelShader(&m_PixelShaderShadow, "BlackShadowPS.cso");

	Scene* scene = Manager::GetScene();
	m_SE = scene->AddGameObject<Audio>(2);
	m_SE->Load("asset\\audio\\dribble.wav");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.03f, 0.03f, 0.03f);
	m_Power = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

void PLAYER::Uninit()
{
	/*m_VertexBuffer->Release();
	m_Texture->Release();*/
	m_Model->Unload();
	key = false;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void PLAYER::Update()
{
	Scene* scene = Manager::GetScene();


	//�`���[�g���A���̂Ƃ�
	if (scene->GetSceneNumber() == 3)
	{
		PLAYER::PlayerRange(scene);
		PLAYER::playerTutolialMove(scene);
		if (m_Step >= 3)
		{
			command = inputhendler->InputHundle();

			if (command)
			{
				command->execute(this);
			}
			//PLAYER::playerholdball(scene);
		}

	}

	//�Q�[���V�[���̂Ƃ�
	if (scene->GetSceneNumber() == 2)
	{
		PLAYER::PlayerRange(scene);

		PLAYER::playerholdball(scene);

		//PLAYER::playermove();
	}

}

void PLAYER::Draw()
{
	//�r���[�}�g���N�X�ݒ�
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);

	if (!camera->ChecView(m_Position))
	{
		return;
	}

	m_Model->Update("Idle", "Run", m_Brendlate, m_Frame[0]);

	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + D3DX_PI, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);


	//Renderer::SetWorldViewProjection2D();

	m_Model->Draw();


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

	m_Model->Draw();

}

//�v���C���[���{�[�������A�����Ă���Ƃ��̏���
void PLAYER::playerholdball(Scene* scene)
{

	FootBall* football = scene->GetGameObject<FootBall>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);
	GaugeBack* gaugeback = scene->GetGameObject<GaugeBack>(2);
	GaugeRed* gaugered = scene->GetGameObject<GaugeRed>(2);


	D3DXVECTOR3 Direction = m_Position - football->GetPosition();
	float Length = D3DXVec3Length(&Direction);

	D3DXVECTOR3 Footballforward = football->GetForward();
	D3DXVECTOR3 Playerforward = PLAYER::GetForward();



	//�{�[���ƃv���C���[�̋�����1.5�ȉ��Ȃ�

	if (Length < 1.5f && m_Frame[1] >= 10)
	{

		m_HoldBall = true;//�{�[����ێ����Ă���
	}

	//�{�[����ێ����Ă���Ƃ�
	if (m_HoldBall == true)
	{

		m_Frame[1]++;

		//�v���C���[�̑����Ƀ{�[����
		football->SetPosition(m_Position + Playerforward * 3);

		float a = D3DXVec3Dot(&Playerforward, &Footballforward);

		//��̃t�H���[�h�����������łȂ��Ȃ�
		if (a < 0.99f)
		{
			football->SetRotation(m_Rotation);
		}

		//�V���[�g�{�^���������ݎ�
		if (GetKeyboardPress(DIK_J) || IsButtonPressed(0,BUTTON_B))
		{
			m_Kickform = true;
			gaugeback->SetAlpha(true);
			gaugered->SetAlpha(true);
			m_ShotFrame++;
			m_Power += D3DXVECTOR3(0.0f, 0.1f, 0.1f);
		}
		if (GetKeyboardRelease(DIK_J) || IsButtonReleased(0, BUTTON_B) || m_ShotFrame >= 40)//���������ɒe���R��
		{
			D3DXVECTOR3 GoalDirection = goal->GetPosition() - football->GetPosition();
			float GoalLength = D3DXVec3Length(&GoalDirection);

			if (m_ShotFrame <= 30 && m_ShotFrame >= 10)
			{

				int time = int(GoalLength / m_Power.z);
				float m_power_Y = 9.0f / time + (((9.8f / 60) * time) / 2);
				m_Power.y = m_power_Y;
			}


			football->Shoot(m_Power.y, m_Power.z);
			gaugeback->SetAlpha(false);
			gaugered->SetAlpha(false);
			m_HoldBall = false;
			m_Kickform = false;
			m_Power = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_ShotFrame = 0;
			m_SE->Play(false, 0.2f);
		}
		//�R���g���[���V���[�g
		if (GetKeyboardPress(DIK_L))
		{
			m_Power += D3DXVECTOR3(0.08f, 0.1f, 0.1f);
			m_Kickform = true;
			gaugeback->SetAlpha(true);
			gaugered->SetAlpha(true);
			m_ShotFrame++;
		}
		if (GetKeyboardRelease(DIK_L) || m_ShotFrame >= 40)//���������ɒe���R��
		{
			D3DXVECTOR3 GoalDirection = goal->GetPosition() - football->GetPosition();
			float GoalLength = D3DXVec3Length(&GoalDirection);

			if (m_ShotFrame <= 30 && m_ShotFrame >= 10)
			{

				int time = int(GoalLength / m_Power.z);
				float m_power_Y = 9.0f / time + ((9.8f / 60) * time) / 2;

				m_Power.y = m_power_Y;
			}

			football->CurveShoot(m_Power.x, m_Power.y, m_Power.z);
			gaugeback->SetAlpha(false);
			gaugered->SetAlpha(false);
			m_HoldBall = false;
			m_Kickform = false;
			m_Power = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_ShotFrame = 0;
			m_SE->Play(false, 0.2f);
		}

		//�p�X
		if (GetKeyboardTrigger(DIK_K))
		{
			football->Pass(5.0f, 0.0f);
			m_HoldBall = false;
			m_Frame[1] = 0;
		}
	}

	if (m_HoldBall == false)
	{
		m_Frame[1]++;
	}


}

//�v���C���[�̃`���[�g���A�����̋���
void PLAYER::playerTutolialMove(Scene* scene)
{
	ControlUI* controlUI = scene->GetGameObject<ControlUI>(2);
	Transition* transition = scene->GetGameObject<Transition>(2);

	//�������牺�͈ړ�

	if (m_Step == 0 && controlUI->GetFrame() == 1)//�`���[�g���A���O�i
	{
		if (GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_UP))
		{

			m_Position.z +=  m_Speed * 0.6;
			m_Frame[0]++;

		}

		//600�t���[���A3�b�o������
		if (m_Frame[0] >= 60 * 3)
		{
			//���̃X�e�b�v�ց@
			m_Step = 2;
			m_Frame[0] = 0;
			m_Position = D3DXVECTOR3(0.0f, 0.0f, -30.0f);
		}
	}
	else if (m_Step == 2)//�`���[�g���A��2�͌��ƍ��E
	{
		if (GetKeyboardPress(DIK_A) || IsButtonPressed(0,BUTTON_LEFT))
		{
			m_Rotation.y = -D3DX_PI / 2;
			m_Position.x -= m_Speed * 0.6;
			m_Frame[0]++;

		}
		if (GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT))
		{

			m_Rotation.y = D3DX_PI / 2;

			m_Position.x += m_Speed * 0.6;

			m_Frame[0]++;

		}
		if (GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_DOWN))
		{
			m_Rotation.y = D3DX_PI;

			m_Position.z -= m_Speed * 0.3;

			m_Frame[0]++;
		}

		if (m_Frame[0] >= 60 * 6)
		{
			m_Step = 3;
			m_Frame[0] = 0;
			m_Position = D3DXVECTOR3(0.0f, 0.0f, -40.0f);
		}
	}
	else if (m_Step == 3)//�{�[����ێ�����
	{
		m_Frame[0]++;

		//PLAYER::playermove();
		if (m_HoldBall == true)
		{
			m_Step = 4;
			m_Frame[0] = 0;
		}

	}
	else if (m_Step == 4)//�{�[�����V���[�g
	{
		m_Frame[0]++;
		//PLAYER::playermove();
		PLAYER::playerholdball(scene);

		if (GetKeyboardRelease(DIK_J) || GetKeyboardRelease(DIK_L)
			|| IsButtonReleased(0,BUTTON_B))
		{
			m_Step = 5;
			m_Frame[0] = 0;
		}
	}
	else if (m_Step == 5)//�ꏊ���̃��Z�b�g
	{

		if (GetKeyboardPress(DIK_SPACE) || IsButtonPressed(0, BUTTON_A))
		{
			m_Step = 6;
		}

	}
	else if (m_Step == 6)//���R����
	{

		m_Frame[0]++;

		//PLAYER::playermove();
		PLAYER::playerholdball(scene);
		if (m_Frame[0] >= 60 * 30)
		{
			m_Step = 7;
			m_Frame[0] = 0;
			m_Position = D3DXVECTOR3(0.0f, 0.0f, -40.0f);
		}

	}
	else if (m_Step == 7)
	{
		m_Frame[0] ++;
		if (m_Frame[0] >= 10)
		{
			m_Step = 8;
		}
	}

	if (m_Step <= 2)
	{
		//�h���u���ƃA�C�h���̃`�F���W�����������
		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_D))
		{
			m_dribble = true;
			m_idlechange = true;
		}
		else
		{
			m_dribble = false;
			m_idlechange = false;
		}

		//�v���C���[�̑̂�ҋ@���瑖��ɕω�������
		if (m_idlechange == true)
		{
			m_AnimationName = "Run";
			m_Brendlate += 0.04f;
			if (m_Brendlate >= 1.5f)
			{
				m_Brendlate = 1.5f;
			}
		}
		else
		{
			m_AnimationName = "Idle";
			m_Brendlate -= 0.08f;
			if (m_Brendlate <= 0.0f)
			{
				m_Brendlate = 0.0f;
			}
		}

	}

}

//�v���C���[�̍s���͈�
void PLAYER::PlayerRange(Scene* scene)
{
	MeshField* meshfield = scene->GetGameObject<MeshField>(1);
	//�ȍ~�v���C���[�̃v���C�\�͈�
	if (m_Position.x >= 9.9 * 5.0f)
	{
		m_Position.x = 9.9 * 5.0f;
	}
	if (m_Position.x <= -10 * 5.0f)
	{
		m_Position.x = -50.0f;
	}

	if (m_Position.z >= 10 * 5.0f)
	{
		m_Position.z = 10 * 5.0f;
	}
	if (m_Position.z <= -10 * 5.0f)
	{
		m_Position.z = -50.0f;
	}

	//�v���C���[��n�ʂɐݒu������
	m_Position.y = meshfield->GetHeight(m_Position);


	//�Q�[�����̃v���C���[�ړ�
	//void PLAYER::playermove()
	//{
	//
	//	//�L�b�N���Ă��Ȃ��Ƃ��݈̂ړ��\
	//	if (m_Kickform == false)
	//	{
	//		//�������牺�͈ړ��L�[�{�[�h
	//		if (GetKeyboardPress(DIK_A))
	//		{
	//			m_Rotation.y = -D3DX_PI / 2;
	//			m_Position.x -= m_Speed * 0.6;
	//
	//		}
	//		if (GetKeyboardPress(DIK_D) )
	//		{
	//
	//			m_Rotation.y = D3DX_PI / 2;
	//
	//			m_Position.x += m_Speed * 0.6;
	//
	//		}
	//		if (GetKeyboardPress(DIK_S) )
	//		{
	//			m_Rotation.y = D3DX_PI;
	//
	//			m_Position.z -= m_Speed * 0.3;
	//
	//
	//		}
	//
	//		if (GetKeyboardPress(DIK_W) )
	//		{
	//			m_Rotation.y =  0.0f;
	//			m_Position.z +=  m_Speed * 0.6;
	//
	//		}
	//		if (IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, BUTTON_RIGHT)
	//			|| IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, BUTTON_LEFT))  //�Q�[���p�b�h
	//		{
	//			m_Rotation.y =  - (GetLeftStickAngle(0) - D3DX_PI /2);
	//			m_Position += PLAYER::GetForward() * 0.5f;
	//		}
	//
	//
	//		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_D)
	//			|| IsButtonPressed(0, BUTTON_LEFT) || IsButtonPressed(0, BUTTON_RIGHT) || IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, BUTTON_UP))
	//		{
	//			m_dribble = true;
	//			m_idlechange = true;
	//		}
	//		else
	//		{
	//			m_dribble = false;
	//			m_idlechange = false;
	//		}
	//
	//	}
	//
	//
	//	//�v���C���[����]������
	//	if (GetKeyboardPress(DIK_Q))
	//	{
	//		m_Rotation -= D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	//	}
	//	//�v���C���[����]������
	//	if (GetKeyboardPress(DIK_E))
	//	{
	//		m_Rotation += D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	//	}
	//
	//
	//	if (GetKeyboardTrigger(DIK_SPACE) || IsButtonPressed(0, BUTTON_A))
	//	{
	//
	//		m_AnimationName = "Idle";
	//		m_idlechange = false;
	//	}
	//	//�v���C���[�̑̂�ҋ@���瑖��ɕω�������
	//	if (m_idlechange == true)
	//	{
	//		m_AnimationName = "Run";
	//		m_Brendlate += 0.04f;
	//		if (m_Brendlate >= 1.5f)
	//		{
	//			m_Brendlate = 1.5f;
	//		}
	//	}
	//	else
	//	{
	//		m_AnimationName = "Idle";
	//		m_Brendlate -= 0.08f;
	//		if (m_Brendlate <= 0.0f)
	//		{
	//			m_Brendlate = 0.0f;
	//		}
//}
}