#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "aroundstate.h"
#include "doState.h"
#include "manager.h"
#include "scene.h"
#include "waitState.h"
#include "approachstate.h"
#include "discoverstate.h"
#include "slidingState.h"
#include "player.h"
#include "enemy.h"
#include "goal.h"

void AroundState::Init()
{


}

void AroundState::Uninit()
{

}

void AroundState::Update()
{
	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	Goal* goal = scene -> GetGameObject<Goal>(1);

	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 enemyPos = m_Enemy->GetPosition();
	D3DXVECTOR3 enemyforward = m_Enemy->GetForward(); 


	D3DXVECTOR3 Direction = playerPos - enemyPos;

	D3DXVECTOR3 GoalDierction = playerPos - goal->GetPosition();


	float angle = D3DXVec3Dot(&enemyforward , &Direction);

	float Length = D3DXVec3Length(&Direction);
	float PlayerLength = D3DXVec3Length(&GoalDierction);

	StateCount = 3;

	if (PlayerLength >= -10.0f && player->GetPlayerHold() == true)//ゴールに近づいたら
	{
		m_Enemy->NextState(new DiscoverState(m_Enemy));
	}

	if (Length >= 10.0f)//遠くなったら
	{
		m_Enemy->NextState(new DoState(m_Enemy));
	}
	if (player->GetPlayerHold() == false)//プレイヤーがボールを持ってない状態なら
	{
		m_Enemy->NextState(new WaitState(m_Enemy));
	}
		
}