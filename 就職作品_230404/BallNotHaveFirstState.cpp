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
	
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����


	if (m_Num == 100)
	{

		m_Num = rand() % 2;//0~3�̕ϐ��������_����
	}


	if (m_Enemy->GetStateCount() == 0)
	{
		if (player->GetPlayerHold() == true)//�{�[�������Ă���State�Ɉȍ~
		{

			m_Enemy->NextState(new WaitState(m_Enemy));

		}
		else //��ێ��̂Ƃ�
		{
			if (m_Num == 0)//�����_���Ɍ���
			{
				m_Num = 100;
				m_Enemy->NextBallNotHaveState(new BallNotRandomState(m_Enemy));//�p�j

			}
			else
			{
				m_Num = 100;
				m_Enemy->NextBallNotHaveState(new BallNotWaitState(m_Enemy));//�~�܂�

			}
		}

	}
	
}
