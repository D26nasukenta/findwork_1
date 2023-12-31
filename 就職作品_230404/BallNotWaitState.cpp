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

	//プレイヤーを向く式
	float forward = atan2f(player->GetPosition().x - m_Enemy->GetPosition().x,
		player->GetPosition().z - m_Enemy->GetPosition().z);

	m_Enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));



	if (m_Frame >= SECOND * 2)//2秒経過したら
	{
		m_Frame = 0;
		m_Enemy->NextBallNotHaveState(new BallNotRandomState(m_Enemy));//徘徊

	}

	if (player->GetPlayerHold() == true)//ボールを保持する状態になったら
	{

		m_Enemy->NextBallNotHaveState(new BallNotHaveFirstState(m_Enemy));//徘徊
		m_Enemy->NextState(new WaitState(m_Enemy));


	}

}
