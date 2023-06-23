#include "manager.h"
#include "waitState.h"
#include "aroundstate.h"
#include "doState.h"
#include "scene.h"
#include "football.h"
#include "player.h"
#include "goal.h"
#include "enemy.h"
#include "FirstState.h"

void FirstState::Init()
{
	
}

void FirstState::Uninit()
{
}

void FirstState::Update()
{

	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);

	StateCount = 0;

	D3DXVECTOR3 Direction = FirstPos - player->GetPosition();
	float Length = D3DXVec3Length(&Direction);


	if (player->GetPlayerHold() == true)
	{
		if (Length <= 20.0f)//ƒ][ƒ“‚Ì’†‚È‚ç
		{

			m_Enemy->NextState(new DoState(m_Enemy));

		}
		else//ƒ][ƒ“‚ÌŠO‚È‚ç
		{

			m_Enemy->NextState(new WaitState(m_Enemy));
		}

	}
}
