#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "manager.h"
#include "scene.h"
#include "football.h"
#include "player.h"
#include "goal.h"
#include "enemy.h"
#include "waitState.h"
#include "BallNotWaitState.h"
#include "BallNotRandomState.h"

void BallNotRandomState::Init()
{
}

void BallNotRandomState::Uninit()
{
}

void BallNotRandomState::Update()
{
	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);
	m_Frame++;


	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化


	if (m_Num == 100)
	{

		m_Num = rand() % 4;//0~3の変数をランダムに
	}

	if (m_Num != 3)
	{
		m_Enemy->SetRotate(D3DXVECTOR3(0.0f, 0.01f, 0.0f));
	}
	else
	{
		m_Enemy->SetRotate(D3DXVECTOR3(0.0f, -0.01f, 0.0f));
	}

	m_Enemy->SetMovement(m_Enemy->GetForward() * 0.5);

	/*float forward = atan2f(player->GetPosition().x - m_Enemy->GetPosition().x,
		player->GetPosition().z - m_Enemy->GetPosition().z);

	m_Enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));
	football->GetPosition();*/

	if (m_Frame >= 60 && player->GetPlayerHold() == false)//１秒経過したら
	{
		m_Num = 100;
		m_Enemy->NextBallNotHaveState(new BallNotWaitState(m_Enemy));//待ち
	}

	if (player->GetPlayerHold() == true)//ボール保持
	{

		m_Enemy->NextState(new WaitState(m_Enemy));

	}
}
