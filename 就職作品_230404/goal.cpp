#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"main.h"
#include "manager.h"
#include "meshfield.h"
#include "model.h"
#include"renderer.h"
#include "audio.h"
#include "goal.h"
#include "player.h"
#include "enemy.h"
#include "football.h"
#include "scene.h"
#include "score.h"
#include "goal2D.h"

#define SCALE 1.0f

void Goal::Init()
{
	g_Model = new Model();
	g_Model->Load("asset\\model\\soccergoal_003.obj");

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "pixelLightingPS.cso");

	Renderer::CreatePixelShader(&m_PixelShaderShadow, "BlackShadowPS.cso");

	Scene* scene = Manager::GetScene();
	m_SE = scene->AddGameObject<Audio>(2);
	m_SE->Load("asset\\audio\\hoissle.wav");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(32.0f, 12.0f, 10.0f);

}

void Goal::Uninit()
{
	/*m_VertexBuffer->Release();
	m_Texture->Release();*/
	g_Model->Unload();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Goal::Update()
{
	Goal::GoalJudge();

}

void Goal::Draw()
{

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	g_Model->Draw();

	// 影行列生成
	D3DXMatrixIdentity(&g_MatrixShadow);


	
	// 影行列を生成するD3DXMatrixShadow()関数がDirectXに実装されている
	D3DXPLANE plane;
	D3DXVECTOR3 pt = { 0, 0.1f, 0 }, nor = { 0, 1, 0 };
	D3DXPlaneFromPointNormal(
		&plane,	// 平面を表すD3DXPLANE構造体
		&pt,	// 平面上の任意の点
		&nor);	// 平面の法線ベクトル
	D3DXMatrixShadow(&g_MatrixShadow, &g_light, &plane);

	D3DXMatrixMultiply(&world, &world, &g_MatrixShadow);
	Renderer::SetWorldMatrix(&world);

	Renderer::GetDeviceContext()->PSSetShader(m_PixelShaderShadow, NULL, 0);

	g_Model->Draw();

}

void Goal::GoalJudge()
{
	Scene* scene = Manager::GetScene();

	FootBall* football = scene->GetGameObject<FootBall>(1);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	ENEMY* enemy = scene->GetGameObject<ENEMY>(1);
	Goal2D* goal2d = scene->GetGameObject<Goal2D>(2);
	Score* score = scene->GetGameObject<Score>(2);

	D3DXVECTOR3 g_direction = football->GetPosition() - m_Position;

	//ゴールの一番前のみに当たり判定を作るためOBB不採用
	if (football->GetPosition().x > m_Position.x - m_Scale.x / 2 &&
		football->GetPosition().x < m_Position.x + m_Scale.x / 2 &&
		football->GetPosition().y < m_Position.y + m_Scale.y &&
		football->GetPosition().z > m_Position.z - m_Scale.z / 2 &&
		football->GetPosition().z < m_Position.z - m_Scale.z / 2 + 2.0f)
	{
		m_Score += 1;
		player->SetHoldState(false);
		score->SetScore(m_Score);
		football->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
		football->SetVel(0.0f, 0.0f, 0.0f);
		m_SE->Play(false, 0.2f);
		goal2d->SetAlpha(true);

		m_goalCheck = true;
	}
	if (m_goalCheck == true)
	{
		
		m_Frame++;
		if (m_Frame >= 5)
		{
			m_goalCheck = false;
		}
	}
}
