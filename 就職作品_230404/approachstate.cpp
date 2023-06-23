#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "doState.h"
#include "scene.h"
#include "manager.h"
#include "waitState.h"
#include "discoverstate.h"
#include "approachstate.h"
#include "football.h"
#include "goal.h"
#include "player.h"
#include "enemy.h"

void ApproachState::Init()
{



}

void ApproachState::Uninit()
{

}

void ApproachState::Update()
{
	D3DXVECTOR3 m_Movement;

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	Scene* scene = Manager::GetScene();
	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);

	D3DXVECTOR3 enemyforward = enemy->GetForward();

	//各ポジション変数を格納
	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 enemyPos = enemy->GetPosition();
	D3DXVECTOR3 goalPos = goal->GetPosition();

	//2つのオブジェクト間の引き算
	D3DXVECTOR3 GoalDirection = goalPos - playerPos;
	D3DXVECTOR3 EnemyDirection = goalPos - enemyPos;

	StateCount = 2;

	//ゴールとプレイヤーの中点を求める
	D3DXVECTOR3 PointM = D3DXVECTOR3((goalPos.x + playerPos.x) / 2, 0.0f,
		(goalPos.z + playerPos.z) / 2);
	//ゴールとプレイヤーの中点を見る	
	float forward = atan2f(PointM.x - enemy->GetPosition().x,
		PointM.z - enemy->GetPosition().z);
	//距離を求める
	float PlayerLength = D3DXVec3Length(&GoalDirection);
	float EnemyLength = D3DXVec3Length(&EnemyDirection);

	if (EnemyLength + 0.4 * PlayerLength > PlayerLength ) //ディフェンダーの距離がプレイヤーより遠いと
	{
		enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));//中点を見て下で移動
		enemy->SetMovement(enemy->GetForward() * 0.8f);

	}
	else
	{
		m_Enemy->NextState(new DoState(m_Enemy));
	}



}