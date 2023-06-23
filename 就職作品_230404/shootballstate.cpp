#include "main.h"
#include "scene.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "goal.h"
#include "meshfield.h"
#include "football.h"
#include "checkballstate.h"
#include "enemyholdballstate.h"
#include "ballholdstate.h"
#include "shootballstate.h"

void ShootBallState::Init()
{
}

void ShootBallState::Uninit()
{
}

void ShootBallState::Update()
{
	Scene* scene = Manager::GetScene();
	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	MeshField* meshfield = scene->GetGameObject<MeshField>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);


}

