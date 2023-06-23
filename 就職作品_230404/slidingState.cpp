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
#include "football.h"
#include "player.h"
#include "enemy.h"
#include "slidingState.h"

void SlidingState::Init()
{



}


void SlidingState::Uninit()
{
}

void SlidingState::Update()
{
	m_Frame++;

	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);

	//“G‚ªƒvƒŒƒCƒ„[‚ÉŒü‚«‘±‚¯‚é•Ï”
	float forward = atan2f(football->GetPosition().x - m_Enemy->GetPosition().x,
		football->GetPosition().z - m_Enemy->GetPosition().z);


	D3DXVECTOR3 Direction = m_Enemy->GetPosition() - player->GetPosition();
	D3DXVECTOR3 BallDirection = m_Enemy->GetPosition() - football->GetPosition();
	float Length = D3DXVec3Length(&Direction);
	float BallLength = D3DXVec3Length(&BallDirection);

	StateCount = 4;

	if (m_once == false)
	{
		
		m_Enemy->SetRotation(D3DXVECTOR3(-1.0f, forward, 0.0f));
	}
	if (m_Frame <= 60)
	{

		m_once = true;
		m_Enemy->SetMovement(m_Enemy->GetForward() * 1.0f);

		if (BallLength < 0.6)
		{
			m_Enemy->SetHoldState(true);
			player->SetHoldState(false);
		}

	}
	else
	{
		m_Frame = 0;
		m_Enemy->NextState(new WaitState(m_Enemy));
	}


}
