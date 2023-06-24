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
	
	//�L�[�p�[�ƃ{�[���̋���
	float Direction = football->GetPosition().z - goalkeeper->GetPosition().z;

	float Length = fabs(Direction);//��Βl�ɕϊ�

	float time	=  Length / football->GetFirstVelY(); //����/�����Ń{�[�������B���鎞�Ԃ����߂�

	//�S�[���Ƀ{�[����������Y���W�̈ʒu(���������グ�̎�)
	float FY = football->GetFirstVelY() * time - (((9.8 / 60) * time * time) / 2);
	m_Frame++;

	StateCount = 2;

	//�{�[���̎��ɑ΂��Ĉړ�����
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
	//�S�[���ڂ̑O�Ń{�[���̍�����5.0f�ȏ�@���@���B��5�t���[���O��
	if (FY > 5.0f && goalkeeper->GetJumpState() == false  && int(time) - 5 > m_Frame )
	{

			goalkeeper->SetJumpState(true);

		
	}

	if (goalkeeper->GetHoldState() == true || goal->GetGoalCheck() == true || football->GetFirstVelZ() == 0.0f)
	{
		m_Keeper->NextState(new KeeperStayState (m_Keeper));
	}


}
