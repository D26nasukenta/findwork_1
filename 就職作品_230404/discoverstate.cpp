#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "doState.h"
#include "scene.h"
#include "manager.h"
#include "waitState.h"
#include "discoverstate.h"
#include "FirstState.h"
#include "slidingState.h"
#include "tacklestate.h"
#include "player.h"
#include "enemy.h"
#include "goal.h"

void DiscoverState::Init()
{



}

void DiscoverState::Uninit()
{

}

void DiscoverState::Update()
{

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	D3DXVECTOR3 m_Movement;

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	Goal* goal = scene->GetGameObject < Goal >(1);

	D3DXVECTOR3 enemyforward = m_Enemy->GetForward();


	D3DXVECTOR3 enemyPos = m_Enemy->GetPosition();


	//エネミーとプレイヤー距離
	D3DXVECTOR3 Direction = enemyPos - playerPos;
	float Length = D3DXVec3Length(&Direction);

	//敵がプレイヤーに向き続ける変数
	float forward = atan2f(playerPos.x - m_Enemy->GetPosition().x,
		playerPos.z - m_Enemy->GetPosition().z);

	m_Enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));

	//ゴールとプレイヤー距離
	D3DXVECTOR3 GoalDirection = playerPos - goal->GetPosition();
	GoalLength = D3DXVec3Length(&GoalDirection);


	//前回の長さが今の長さより短かったら
	if (player->GetPosition().z < playerPos.z)
	{
		playerPos = player->GetPosition();
		m_Enemy->SetMovement(player->GetForward()* 0.5f);

	}
	else if (player->GetPosition().z > playerPos.z)
	{
		playerPos = player->GetPosition();
		m_Enemy->SetMovement(player->GetForward() * -0.5f);

	}


	if (GoalLength < 30.0f)
	{
		m_Enemy->NextState(new DoState(m_Enemy));
	}

	if (Length < 10.0f && player->GetPlayerHold() == true)
	{
		float denominator = Length * 5.0f;
		m_Random = rand() % (int)denominator;//プレイヤーと敵の距離で割る、距離が近くなるほど値が少なくなる

		if (m_Random >= 20.0f)
		{
			m_Enemy->NextState(new FirstState(m_Enemy));

		}
	else if (m_Random < 20.0f && m_Random > 5.0f)
		{
			m_Enemy->NextState(new TackleState(m_Enemy));
		}
		else
		{
			m_Enemy->NextState(new SlidingState(m_Enemy));
		}

	}


}