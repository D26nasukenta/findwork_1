#include "manager.h"
#include "scene.h"
#include "football.h"
#include "player.h"
#include "goal.h"
#include "enemy.h"
#include "waitState.h"
#include "BallNotHaveFirstState.h"
#include "BallNotWaitState.h"
#include "BallNotRandomState.h"

#define SECOND	60

void BallNotWaitState::Init()
{
}

void BallNotWaitState::Uninit()
{
}

void BallNotWaitState::Update()
{

	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	
	m_Frame++;

	//ƒvƒŒƒCƒ„[‚ðŒü‚­Ž®
	float forward = atan2f(player->GetPosition().x - m_Enemy->GetPosition().x,
		player->GetPosition().z - m_Enemy->GetPosition().z);

	m_Enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));



	if (m_Frame >= SECOND * 2)//2•bŒo‰ß‚µ‚½‚ç
	{
		m_Frame = 0;
		m_Enemy->NextBallNotHaveState(new BallNotRandomState(m_Enemy));//œpœj

	}

	if (player->GetPlayerHold() == true)//ƒ{[ƒ‹‚ð•ÛŽ‚·‚éó‘Ô‚É‚È‚Á‚½‚ç
	{

		m_Enemy->NextBallNotHaveState(new BallNotHaveFirstState(m_Enemy));//œpœj
		m_Enemy->NextState(new WaitState(m_Enemy));


	}

}
