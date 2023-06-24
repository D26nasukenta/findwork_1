#include "manager.h"
#include "waitState.h"
#include "aroundstate.h"
#include "doState.h"
#include "scene.h"
#include "football.h"
#include "player.h"
#include "goal.h"
#include "enemy.h"

#include "BallNotHaveFirstState.h"
#include "FirstState.h"


void WaitState::Init()
{

}

void WaitState::Uninit()
{

}

void WaitState::Update()
{

	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);

	//プレイヤーの真正面を向く式
	float forward = atan2f(player->GetPosition().x - m_Enemy->GetPosition().x,
		player->GetPosition().z - m_Enemy->GetPosition().z);


	m_Enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));
	football->GetPosition();
	
	StateCount = 1;

	D3DXVECTOR3 Direction = FirstPos - player->GetPosition();
	float Length = D3DXVec3Length(&Direction);

	if (player->GetPlayerHold() == true && Length <= 20.0f)//ボールを持っていてディフェンダーの最初のポジションからの距離
	{
		 
			m_Enemy->NextState(new DoState (m_Enemy));
	}
	else if (m_Enemy->GetPosition().z >= FirstPos.z+ 0.5f || m_Enemy->GetPosition().z <= FirstPos.z -0.5f)
	{
		//最初の位置を向く式
		float BackForward = atan2f(FirstPos.x - m_Enemy->GetPosition().x,
			FirstPos.z - m_Enemy->GetPosition().z);
		m_Enemy->SetRotation(D3DXVECTOR3(0.0f, BackForward, 0.0f));
		m_Enemy->SetMovement(m_Enemy->GetForward() * 0.5f);
		
	}
	
}