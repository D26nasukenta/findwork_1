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
#include "audio.h"

#include "meshfield.h"
#include "state.h"

#include "FirstState.h"
#include "slidingState.h"

#include "BallNotHaveFirstState.h"

void ENEMY::Init()
{
	g_Model = new Model();
	g_Model->Load((char*)"asset\\model\\DF_001.obj");

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "pixelLightingPS.cso");

	Renderer::CreatePixelShader(&m_PixelShaderShadow, "BlackShadowPS.cso");

	Scene* scene = Manager::GetScene();
	m_SE = scene->AddGameObject<Audio>(2);
	m_SE->Load("asset\\audio\\sliding.wav");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

	m_State = new FirstState(this);
	m_NextState = new FirstState(this);

	/*m_BallNotHaveState = new BallNotHaveFirstState(this);
	m_NextBallNotHaveState = new BallNotHaveFirstState(this);*/

}

void ENEMY::Uninit()
{
	/*m_VertexBuffer->Release();
	m_Texture->Release();*/
	g_Model->Unload();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void ENEMY::Update()
{
	Scene* scene = Manager::GetScene();
	MeshField* meshfield = scene->GetGameObject<MeshField>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);

	m_Position.y = meshfield->GetHeight(m_Position);


	//CheckBallNotHaveState();
	CheckState();

	//m_BallNotHaveState->Update();
	m_State->Update();


	if (m_BallHold == true)
	{
		football->SetPosition(m_Position);
		m_Time++;
	}
	if (m_Time >= 10)
	{
		m_Time = 0;
		m_BallHold = false;
		football->SetPosition(D3DXVECTOR3(0.0f,0.0f,-30.0f));
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

void ENEMY::Draw()
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

	//Renderer::SetWorldViewProjection2D();

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

	if(GetKeyboardPress(DIK_2))
	{

		ImGui::Begin("State Defender Number");                     // Create a window called "Hello, world!" and append into it.


		ImGui::Text("StateNumber = %d", m_State->GetState());

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

}
