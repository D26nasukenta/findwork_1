#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "doState.h"
#include "scene.h"
#include "manager.h"
#include "waitState.h"
#include "discoverstate.h"
#include "approachstate.h"
#include "football.h"
#include "goal.h"
#include "player.h"
#include "enemy.h"

void ApproachState::Init()
{



}

void ApproachState::Uninit()
{

}

void ApproachState::Update()
{
	D3DXVECTOR3 m_Movement;

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	Scene* scene = Manager::GetScene();
	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);

	D3DXVECTOR3 enemyforward = enemy->GetForward();

	//�e�|�W�V�����ϐ����i�[
	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 enemyPos = enemy->GetPosition();
	D3DXVECTOR3 goalPos = goal->GetPosition();

	//2�̃I�u�W�F�N�g�Ԃ̈����Z
	D3DXVECTOR3 GoalDirection = goalPos - playerPos;
	D3DXVECTOR3 EnemyDirection = goalPos - enemyPos;

	StateCount = 2;

	//�S�[���ƃv���C���[�̒��_�����߂�
	D3DXVECTOR3 PointM = D3DXVECTOR3((goalPos.x + playerPos.x) / 2, 0.0f,
		(goalPos.z + playerPos.z) / 2);
	//�S�[���ƃv���C���[�̒��_������	
	float forward = atan2f(PointM.x - enemy->GetPosition().x,
		PointM.z - enemy->GetPosition().z);
	//���������߂�
	float PlayerLength = D3DXVec3Length(&GoalDirection);
	float EnemyLength = D3DXVec3Length(&EnemyDirection);

	if (EnemyLength + 0.4 * PlayerLength > PlayerLength ) //�f�B�t�F���_�[�̋������v���C���[��艓����
	{
		enemy->SetRotation(D3DXVECTOR3(0.0f, forward, 0.0f));//���_�����ĉ��ňړ�
		enemy->SetMovement(enemy->GetForward() * 0.8f);

	}
	else
	{
		m_Enemy->NextState(new DoState(m_Enemy));
	}



}