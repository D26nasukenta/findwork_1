#include "main.h"
#include "scene.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "football.h"
#include "checkballstate.h"
#include "enemyholdballstate.h"

void EnemyHoldBallState::Init()
{

}

void EnemyHoldBallState::Uninit()
{

}

void EnemyHoldBallState::Update()
{
	Scene* scene = Manager::GetScene();
	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);
	
	m_Frame++;
	football->SetPosition(enemy->GetPosition());
	if (m_Frame >= 120)
	{
	
	m_Frame = 0;
	m_FootBall->NextBallState(new CHeckBallState(m_FootBall));
	}

}
