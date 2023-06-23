#include "main.h"
#include "scene.h"
#include "manager.h"
#include "keepercatchstate.h"
#include "keeperstaystate.h"
#include "player.h"
#include "goalkeeper.h"
#include "goal.h"
#include "football.h"

void KeeperCatchState::Init()
{
}

void KeeperCatchState::Uninit()
{
}

void KeeperCatchState::Update()
{
	Scene* scene = Manager::GetScene();
	FootBall* football = scene->GetGameObject<FootBall>(1);
	GoalKeeper* goalkeeper = scene->GetGameObject<GoalKeeper>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	
	//キーパーとボールの距離
	float Direction = football->GetPosition().z - goalkeeper->GetPosition().z;

	float Length = fabs(Direction);//絶対値に変換

	float time	=  Length / football->GetFirstVelY(); //距離/速さでボールが到達する時間を求める

	//ゴールにボール着く時のY座標の位置(鉛直投げ上げの式)
	float FY = football->GetFirstVelY() * time - (((9.8 / 60) * time * time) / 2);
	m_Frame++;

	StateCount = 2;

	//ボールの軸に対して移動する
	if (football->GetPosition().x > goalkeeper->GetPosition().x)
	{
		
		goalkeeper->SetMovement(D3DXVECTOR3(0.8f,0.0f,0.0f));
		if (football->GetPosition().x == goalkeeper->GetPosition().x)
		{
			goalkeeper->SetPosition(D3DXVECTOR3(football->GetPosition().x, 0.0f, 0.0f));
		}
	
	}
	else if (football->GetPosition().x < goalkeeper->GetPosition().x)
	{

		goalkeeper->SetMovement(D3DXVECTOR3(-0.8f, 0.0f, 0.0f));

	}
	//ゴール目の前でボールの高さが5.0f以上　かつ　到達の5フレーム前に
	if (FY > 5.0f && goalkeeper->GetJumpState() == false  && int(time) - 5 > m_Frame )
	{

			goalkeeper->SetJumpState(true);

		
	}

	if (goalkeeper->GetHoldState() == true || goal->GetGoalCheck() == true || football->GetFirstVelZ() == 0.0f)
	{
		m_Keeper->NextState(new KeeperStayState (m_Keeper));
	}


}
