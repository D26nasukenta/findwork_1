#include "manager.h"
#include "gameobject.h"
#include "audio.h"
#include "scene.h"
#include "camera.h"
#include "title.h"
#include "player.h"
#include "polygon2D.h"
#include "football.h"
#include "meshfield.h"
#include "renderer.h"

Scene* Manager::m_Scene;
//Scene* Manager::m_Scenes[5];

void Manager::Init()
{

	Renderer::Init();
	
	Audio::InitMaster();

	SetScene<Title>();

	//SetScenes<Title>(1);

	/*m_Scene = new Scene();
	m_input = new Input();
	m_Scene->Init();
	m_input->Init();*/

}


void Manager::Uninit()
{

	m_Scene->Uninit();
	//m_input->Init();
	Renderer::Uninit();
	Audio::UninitMaster();
}

void Manager::Update()
{

	m_Scene->Update();
	//m_input->Update();
}

void Manager::Draw()
{
	
	Renderer::Begin();
	
	m_Scene->Draw();

	Renderer::End();
}


