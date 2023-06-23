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
#include "gaugeback.h"
#include "gaugered.h"
#include "polygon2D.h"
#include "goal2D.h"
#include "controlui.h"
#include "titlename.h"
#include "pressspace.h"
#include "titlebg.h"
#include "transition.h"
#include "field.h"
#include "meshfield.h"
#include "camera.h"
#include "player.h"
#include "goalkeeper.h"
#include "enemy.h"
#include "football.h"
#include "studiam.h"
#include "goal.h"
#include "score.h"
#include "skydome.h"
#include "particle.h"
#include "human.h"

#include "title.h"
#include "titlesecond.h"
#include "tutorial.h"
#include "result.h"
#include "game.h"

void Tutorial::Init()
{

	Scene::SetSceneNumber(3);

	AddGameObject<Camera>(0);

	//AddGameObject<Field>(1);
	AddGameObject<Studiam>(1)->SetPosition(D3DXVECTOR3(0.0f, 12.0f, -90.0f));
	AddGameObject<MeshField>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	AddGameObject<PLAYER>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -40.0f));
	AddGameObject<GoalKeeper>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 40.0f));
	AddGameObject<ENEMY>(1);

	AddGameObject<Goal>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 52.0f));

	AddGameObject<FootBall>(1)->SetPosition(D3DXVECTOR3(0.0f, rand() % 60 + 50.0f, -35.0f));

	AddGameObject<SkyDome>(1);

	AddGameObject<GaugeBack>(2);
	AddGameObject<Human>(2);
	AddGameObject<GaugeRed>(2);
	AddGameObject<ControlUI>(2);
	AddGameObject<Polygon2D>(2);
	AddGameObject<Goal2D>(2);
	AddGameObject<Score>(2);

	transition = AddGameObject<Transition>(2);
	transition->Start(true);

}

void Tutorial::Uninit()
{

	Scene::Uninit();

}

void Tutorial::Update()
{

	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);
	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	GoalKeeper* goalkeeper = scene->GetGameObject<GoalKeeper>(1);

	Scene::Update();
	//�`���[�g���A�����I�������t�F�[�h�J�n
	if (player->GetTutorialStep() == 7 )
	{
		m_key = true;
		transition->Start(false);
	}

	//�X�y�[�X�𐄂��`���[�g���A���ڍs�Ƀ��Z�b�g�{�^��
	if ((GetKeyboardPress(DIK_SPACE) || IsButtonTriggered(0, BUTTON_A)) && player->GetTutorialStep() >= 5)
	{
		goalkeeper->SetHoldState(false);
		enemy->SetHoldState(false);
		player->SetHoldState(false);
		player->SetKickState(false);
		football->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
		player->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -40.0f));
		enemy->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	}

	//�t�F�[�h���I������玟�̃V�[����
	if (transition->GetFinish() == true)
	{
		Manager::SetScene<TitleSecond>();

	}
}
