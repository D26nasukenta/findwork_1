#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "doState.h"
#include "scene.h"
#include "manager.h"
#include "waitState.h"
#include "discoverstate.h"
#include "monitoringstate.h"
#include "player.h"
#include "enemy.h"
#include "goal.h"


void MonitoringState::Init()
{



}

void MonitoringState::Uninit()
{

}

void MonitoringState::Update()
{

	srand((unsigned int)time(NULL)); // Œ»ÝŽž‚Ìî•ñ‚Å‰Šú‰»

	Scene* scene = Manager::GetScene();
	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	Goal* goal = scene->GetGameObject<Goal>(1);
	D3DXVECTOR3 playerForward = player->GetForward();

	D3DXVECTOR3 Goallength = player->GetPosition() - goal->GetPosition();


}