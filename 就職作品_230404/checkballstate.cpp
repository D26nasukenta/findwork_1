#include "main.h"
#include "scene.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "goal.h"
#include "football.h"
#include "checkballstate.h"
#include "enemyholdballstate.h"
#include "ballholdstate.h"


void CHeckBallState::Init()
{

}

void CHeckBallState::Uninit()
{

}

void CHeckBallState::Update()
{

	Scene* scene = Manager::GetScene();
	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);

	D3DXVECTOR3 Direction = football->GetPosition() - player->GetPosition();
	D3DXVECTOR3 EnemyDirection = football->GetPosition() - enemy->GetPosition();

	float Length = D3DXVec3Length(&Direction);
	float EnemyLength = D3DXVec3Length(&EnemyDirection);

	D3DXVECTOR3 g_direction = football->GetPosition() - goal->GetPosition();


	D3DXVECTOR3 obbx, obby, obbz;

	float obbLenx, obbLeny, obbLenz;


	obbx = goal->GetObbX();
	obbLenx = D3DXVec3Length(&obbx);
	obbx /= obbLenx;

	obby = goal->GetObbY();
	obbLeny = D3DXVec3Length(&obby);
	obby /= obbLeny;

	obbz = goal->GetObbZ();
	obbLenz = D3DXVec3Length(&obbz);
	obbz /= obbLenz;

	float lenX, lenY, lenZ;

	lenX = D3DXVec3Dot(&obbx, &g_direction);
	lenY = D3DXVec3Dot(&obby, &g_direction);
	lenZ = D3DXVec3Dot(&obbz, &g_direction);


	if (fabs(lenX) < obbLenx && fabs(lenY) < obbLeny && fabs(lenZ) < obbLenz)
	{
		m_FootBall->NextBallState(new EnemyHoldBallState(m_FootBall));
		return;
	}

	if (EnemyLength < 2.5f)
	{
		m_FootBall->NextBallState(new EnemyHoldBallState(m_FootBall));
	}
	if (Length < 2.5f)
	{
		m_FootBall->NextBallState(new BallHoldState(m_FootBall));

	}
}