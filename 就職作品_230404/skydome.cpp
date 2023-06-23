#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"main.h"
#include "manager.h"
#include "model.h"
#include"renderer.h"
#include "scene.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "skydome.h"
#include "meshfield.h"
#include "state.h"

#include "waitState.h"

void SkyDome::Init()
{
	g_Model = new Model();
	g_Model->Load((char*)"asset\\model\\skydome_001.obj");

	


	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");


	m_Position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(100.0f, 100.0f, 100.0f);



}

void SkyDome::Uninit()
{

	g_Model->Unload();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void SkyDome::Update()
{


}

void SkyDome::Draw()
{


	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);
	PLAYER* player = scene->GetGameObject<PLAYER>(1);

	m_Position = player->GetPosition();

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
	
}


