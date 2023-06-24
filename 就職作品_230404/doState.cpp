#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "manager.h"
#include "doState.h"
#include "waitState.h"
#include "approachstate.h"
#include "aroundstate.h"
#include "discoverstate.h"
#include "scene.h"
#include "enemy.h"
#include "goal.h"
#include "player.h"
#include "FirstState.h"
#include "BallNotHaveFirstState.h"

void DoState::Init()
{

	

}

void DoState::Uninit()
{

}

void DoState::Update()
{

	Scene* scene = Manager::GetScene();

	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);

	PLAYER* player = scene->GetGameObject<PLAYER>(1);

	Goal* goal = scene->GetGameObject<Goal>(1);

	m_Frame++;

	//敵がプレイヤーに向き続ける変数
	float forward = atan2f(player->GetPosition().x - enemy->GetPosition().x,
		player->GetPosition().z - enemy->GetPosition().z);
	
	D3DXVECTOR3 playerpos = player->GetPosition();
	D3DXVECTOR3 goalpos = goal->GetPosition();

	D3DXVECTOR3 Direction = enemy->GetPosition() - player->GetPosition();
	D3DXVECTOR3 GoalDirection = goalpos - playerpos;
	D3DXVECTOR3 EnemyDirection = goalpos - enemy->GetPosition();

	
	float Length = D3DXVec3Length(&Direction);
	float PlayerLength = D3DXVec3Length(&GoalDirection);
	float EnemyLength = D3DXVec3Length(&EnemyDirection);
	
	//プレイヤーの方を向いてまっすぐ移動
	enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));
	enemy->SetMovement(enemy->GetForward() * 0.5f);

	D3DXVECTOR3 FirstDirection = FirstPos - player->GetPosition();
	float FirstLength = D3DXVec3Length(&Direction);

	StateCount = 2;
	if (FirstLength <= 20.0f)
	{

	if (Length < 10.0f)//プレイヤーと敵の距離が
	{

		m_Enemy->NextState(new AroundState(m_Enemy));//近くで止まる
	
	}

	if (EnemyLength > PlayerLength)//ゴールの距離が遠いと
	{
		m_Enemy->NextState(new ApproachState(m_Enemy));//戻る
	}

	if (player->GetPlayerHold() == false)
	{
		m_Enemy->NextState(new WaitState(m_Enemy));
	}
	
	}
	else
	{
		m_Enemy->NextState(new WaitState(m_Enemy));
	}
}