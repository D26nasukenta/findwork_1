#include "manager.h"
#include "scene.h"
#include "football.h"
#include "player.h"
#include "goal.h"
#include "enemy.h"
#include "waitState.h"
#include "BallNotHaveFirstState.h"
#include "BallNotWaitState.h"
#include "BallNotRandomState.h"

#define SECOND	60

void BallNotWaitState::Init()
{
}

void BallNotWaitState::Uninit()
{
}

void BallNotWaitState::Update()
{

	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	
	m_Frame++;

	//�v���C���[��������
	float forward = atan2f(player->GetPosition().x - m_Enemy->GetPosition().x,
		player->GetPosition().z - m_Enemy->GetPosition().z);

	m_Enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));



	if (m_Frame >= SECOND * 2)//2�b�o�߂�����
	{
		m_Frame = 0;
		m_Enemy->NextBallNotHaveState(new BallNotRandomState(m_Enemy));//�p�j

	}

	if (player->GetPlayerHold() == true)//�{�[����ێ������ԂɂȂ�����
	{

		m_Enemy->NextBallNotHaveState(new BallNotHaveFirstState(m_Enemy));//�p�j
		m_Enemy->NextState(new WaitState(m_Enemy));


	}

}
