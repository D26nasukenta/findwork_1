#include "main.h"
#include "manager.h"
#include "scene.h"
#include "football.h"
#include "goalkeeper.h"
#include "player.h"
#include "enemy.h"
#include "goal.h"
#include "keeperstaystate.h"
#include "keeperpreparestate.h"
#include "keepercatchstate.h"


void KeeperPrepareState::Init()
{
}

void KeeperPrepareState::Uninit()
{
}

void KeeperPrepareState::Update()
{
	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	GoalKeeper* goalkeeper = scene->GetGameObject<GoalKeeper>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);

	//各ポジション変数を格納
	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 goalkeeperPos = goalkeeper->GetPosition();
	D3DXVECTOR3 goalPos = goal->GetPosition();


	//ゴールとプレイヤーの中点を求める
	D3DXVECTOR3 PointM = D3DXVECTOR3(( playerPos.x - goalPos.x) / 2, 0.0f,
		(goalPos.z - playerPos.z) / 2);

	//キーパーがこちらをみつづける
	float forward = atan2f(player->GetPosition().x - goalkeeper->GetPosition().x,
		player->GetPosition().z - goalkeeper->GetPosition().z);

	goalkeeper->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));

	StateCount = 1;

	//中点よりキーパーの位置が
	if (goalkeeper->GetPosition().x < PointM.x 
		&& goalkeeper->GetPosition().x < goal->GetPosition().x + 16.0f)
	{
		goalkeeper->SetMovement(D3DXVECTOR3(1.0f,0.0f,0.0f));
	}

	if (goalkeeper->GetPosition().x > PointM.x
		&& goalkeeper->GetPosition().x > goal->GetPosition().x - 16.0f)
	{
		goalkeeper->SetMovement(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	}

	//if (goalkeeper->GetPosition().z < PointM.z)
	//{
	//	goalkeeper->SetMovement(D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	//}
	//if (goalkeeper->GetPosition().z > PointM.z)
	//{
	//	goalkeeper->SetMovement(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	//}


	if (player->GetPlayerHold() == false && player->GetPlayerKick() == false && football->GetFirstVelY() >= 0.1f)
	{
		m_Keeper->NextState(new KeeperCatchState(m_Keeper));
	}
	if (player->GetPlayerHold() == false && football->GetFirstVelY() <= 0.0)
	{
		m_Keeper->NextState(new KeeperStayState(m_Keeper));
	}
}
