#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"main.h"
#include "manager.h"
#include "model.h"
#include"renderer.h"
#include "scene.h"
#include "enemy.h"
#include "football.h"

#include "meshfield.h"
#include "goalkeeper.h"

#include "keeperstate.h"
#include "keeperstaystate.h"

void GoalKeeper::Init()
{
	g_Model = new Model();
	g_Model->Load((char*)"asset\\model\\goalkeeper_001.obj");

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "pixelLightingPS.cso");

	Renderer::CreatePixelShader(&m_PixelShaderShadow, "BlackShadowPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f);

	m_State = new KeeperStayState(this);
	m_NextState = new KeeperStayState(this);

}

void GoalKeeper::Uninit()
{
	/*m_VertexBuffer->Release();
	m_Texture->Release();*/
	g_Model->Unload();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void GoalKeeper::Update()
{
	
	CheckState();

	m_State->Update();
	
	GoalKeeper::GoalKeeperMove();

}

void GoalKeeper::Draw()
{

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y , m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y , m_Position.z);
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
	
	if (GetKeyboardPress(DIK_2))
	{

		ImGui::Begin("State Keeper Number");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("StateNumber = %d", m_State->GetState());

		ImGui::End();

	}
}

void GoalKeeper::GoalKeeperMove()
{

	Scene* scene = Manager::GetScene();
	MeshField* meshfield = scene->GetGameObject<MeshField>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);

	D3DXVECTOR3 Direction = football->GetPosition() - m_Position;
	float Length = D3DXVec3Length(&Direction);

	//ボールとの当たり判定
	if (Length < 5.0f)
	{
		m_BallHold = true;
	}
	//ボールを持っているなら
	if (m_BallHold == true)
	{
		football->SetPosition(m_Position);
	}
	//ジャンプ中の処理
	if (m_Jump == true)
	{
		m_vy += m_ry;
		m_Position += GoalKeeper::GetUP() * m_vy;

		//地面についたら(下に速度がある状態)
		if (m_Position.y <= meshfield->GetHeight(m_Position))
		{

			m_Jump = false;

		}
	}

	//ジャンプ状態じゃないなら
	if (m_Jump == false)
	{
		m_vy = 1.8f;
		m_Position.y = meshfield->GetHeight(m_Position);

	}

	//以降プレイヤーのプレイ可能範囲
	if (m_Position.x >= 9.9 * 5.0f)
	{
		m_Position.x = 9.9 * 5.0f;
	}
	if (m_Position.x <= -10 * 5.0f)
	{
		m_Position.x = -50.0f;
	}

	if (m_Position.z >= 10 * 5.0f)
	{
		m_Position.z = 10 * 5.0f;
	}
	if (m_Position.z <= -10 * 5.0f)
	{
		m_Position.z = -50.0f;
	}
}


