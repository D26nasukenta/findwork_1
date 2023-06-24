#include "main.h"
#include "manager.h"
#include "scene.h"
#include "football.h"
#include "goalkeeper.h"
#include "player.h"
#include "enemy.h"
#include "keeperpreparestate.h"
#include "keeperstaystate.h"

void KeeperStayState::Init()
{
}

void KeeperStayState::Uninit()
{
}

void KeeperStayState::Update()
{
	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	GoalKeeper* goalkeeper = scene->GetGameObject<GoalKeeper>(1);

	float forward = atan2f(player->GetPosition().x - goalkeeper->GetPosition().x,
		player->GetPosition().z - goalkeeper->GetPosition().z);

	goalkeeper->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));

	StateCount = 0;
	
	if (player->GetPlayerHold() == true)
	{
		m_Keeper->NextState(new KeeperPrepareState(m_Keeper));
	}

}
