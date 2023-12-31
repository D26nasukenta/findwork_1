#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "waitState.h"
#include "BallNotWaitState.h"
#include "BallNotRandomState.h"
#include "BallNotHaveFirstState.h"

void BallNotHaveFirstState::Init()
{
}

void BallNotHaveFirstState::Uninit()
{
}

void BallNotHaveFirstState::Update()
{
	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化


	if (m_Num == 100)
	{

		m_Num = rand() % 2;//0~3の変数をランダムに
	}


	if (m_Enemy->GetStateCount() == 0)
	{
		if (player->GetPlayerHold() == true)//ボール持ってたらStateに以降
		{

			m_Enemy->NextState(new WaitState(m_Enemy));

		}
		else //非保持のとき
		{
			if (m_Num == 0)//ランダムに決定
			{
				m_Num = 100;
				m_Enemy->NextBallNotHaveState(new BallNotRandomState(m_Enemy));//徘徊

			}
			else
			{
				m_Num = 100;
				m_Enemy->NextBallNotHaveState(new BallNotWaitState(m_Enemy));//止まる

			}
		}

	}
	
}
