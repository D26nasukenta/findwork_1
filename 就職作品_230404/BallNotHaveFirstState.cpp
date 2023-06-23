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
	
	srand((unsigned int)time(NULL)); // Œ»ÝŽž‚Ìî•ñ‚Å‰Šú‰»


	if (m_Num == 100)
	{

		m_Num = rand() % 2;//0~3‚Ì•Ï”‚ðƒ‰ƒ“ƒ_ƒ€‚É
	}


	if (m_Enemy->GetStateCount() == 0)
	{
		if (player->GetPlayerHold() == true)//ƒ{[ƒ‹Ž‚Á‚Ä‚½‚çState‚ÉˆÈ~
		{

			m_Enemy->NextState(new WaitState(m_Enemy));

		}
		else //”ñ•ÛŽ‚Ì‚Æ‚«
		{
			if (m_Num == 0)//ƒ‰ƒ“ƒ_ƒ€‚ÉŒˆ’è
			{
				m_Num = 100;
				m_Enemy->NextBallNotHaveState(new BallNotRandomState(m_Enemy));//œpœj

			}
			else
			{
				m_Num = 100;
				m_Enemy->NextBallNotHaveState(new BallNotWaitState(m_Enemy));//Ž~‚Ü‚é

			}
		}

	}
	
}
