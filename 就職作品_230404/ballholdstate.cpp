#include "main.h"
#include "scene.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "goal.h"
#include "input.h"
#include "football.h"
#include "goal.h"
#include "checkballstate.h"
#include "enemyholdballstate.h"
#include "ballholdstate.h"

void BallHoldState::Init()
{
}

void BallHoldState::Uninit()
{
}

void BallHoldState::Update()
{
	Scene* scene = Manager::GetScene();

	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	//ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	
	FootBall* football = scene->GetGameObject<FootBall>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);
	
	football->SetPosition(player->GetPosition());


	D3DXVECTOR3 g_direction = football->GetPosition() - goal->GetPosition();


	D3DXVECTOR3 obbx, obby ,obbz;

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

	float lenX, lenY,lenZ;

	lenX = D3DXVec3Dot(&obbx, &g_direction);
	lenY = D3DXVec3Dot(&obby, &g_direction);
	lenZ = D3DXVec3Dot(&obbz, &g_direction);


	if (fabs(lenX) < obbLenx && fabs(lenY) < obbLeny && fabs(lenZ) < obbLenz)
	{
		m_FootBall->NextBallState(new EnemyHoldBallState(m_FootBall));
		return;
	}

	if (GetKeyboardTrigger(DIK_J))
	{
		football->Shoot(2.0f, 1.0f);
		m_FootBall->NextBallState(new CHeckBallState(m_FootBall));
	}

	if (GetKeyboardTrigger(DIK_L))
	{
		football->CurveShoot(1.2f, 1.0f, 1.0f);
		m_FootBall->NextBallState(new CHeckBallState(m_FootBall));
	}

	if (GetKeyboardTrigger(DIK_K))
	{
		football->Pass(5.0f, 0.0f);
		m_FootBall->NextBallState(new CHeckBallState(m_FootBall));
	}

}
