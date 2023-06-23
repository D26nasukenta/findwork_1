#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "transition.h"
#include "camera.h"
#include "resultbg.h"


#include "title.h"
#include "game.h"
#include "result.h"

void Result::Init()
{
	//AddGameObject<Camera>(0);

	AddGameObject<ResultBg>(2);

	transition = AddGameObject<Transition>(2);
	transition->Start(true);
}

void Result::Uninit()
{

	Scene::Uninit();

}

void Result::Update()
{

	Scene::Update();

	//�ǂ���̃V�[���ɑJ�ڂ��邩�̃{�^������
	if (GetKeyboardTrigger(DIK_UP) && Selection == 1)
	{

		Selection -= 1;

	}
	if (GetKeyboardTrigger(DIK_DOWN) && Selection == 0)
	{

		Selection += 1;

	}

	//�V�[���J�ڂ̑I���{�^��ENTER
	if (GetKeyboardTrigger(DIK_RETURN))
	{

		transition->Start(false);

	}

	//�t�F�[�h
	if (transition->GetFinish() == true)
	{
		if (Selection == 0)
		{

			Manager::SetScene<Title>();

		}
		else
		{
			Manager::SetScene<Game>();
		}

	}
}
