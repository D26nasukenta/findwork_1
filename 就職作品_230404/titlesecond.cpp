#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "polygon2D.h"
#include "gaugeback.h"
#include "gaugered.h"
#include "goal2D.h"
#include "titlename.h"
#include "pressspace.h"
#include "titlebg.h"
#include "transition.h"
#include "field.h"
#include "meshfield.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "goalkeeper.h"
#include "football.h"
#include "goal.h"
#include "studiam.h"
#include "skydome.h"
#include "particle.h"
#include "human.h"

#include "title.h"
#include "titlesecond.h"
#include "tutorial.h"
#include "game.h"

void TitleSecond::Init()
{

	Scene::SetSceneNumber(1);

	AddGameObject<Camera>(0);

	//AddGameObject<Field>(1);
	AddGameObject<MeshField>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	AddGameObject<Studiam>(1)->SetPosition(D3DXVECTOR3(0.0f, 12.0f, -90.0f));
	AddGameObject<PLAYER>(1);
	AddGameObject<ENEMY>(1);
	AddGameObject<GoalKeeper>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 40.0f));

	AddGameObject<Goal>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 52.0f));
	for (int i = 0; i < 45; i++)
	{

		AddGameObject<FootBall>(1)->SetPosition(D3DXVECTOR3(rand() % 60 - 30.0f, rand() % 60 + 50.0f, rand() % 60 - 30.0f));

	}

	AddGameObject<SkyDome>(1);

	AddGameObject<Polygon2D>(2);
	AddGameObject<Particle>(2);
	AddGameObject<Human>(2);
	//AddGameObject<TitleBG>(2);
	AddGameObject<GaugeBack>(2);
	AddGameObject<GaugeRed>(2);
	AddGameObject<Goal2D>(2);
	AddGameObject<TitleName>(2);
	AddGameObject<PressSpace>(2);

	transition = AddGameObject<Transition>(2);
	transition->Start(true);

}

void TitleSecond::Uninit()
{

	Scene::Uninit();

}

void TitleSecond::Update()
{

	Scene::Update();
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		transition->Start(false);
	}


	if (transition->GetFinish() == true)
	{
		Manager::SetScene<Game>();

	}

}
