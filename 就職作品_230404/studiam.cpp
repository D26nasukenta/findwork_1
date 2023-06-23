#include"main.h"
#include "manager.h"
#include "model.h"
#include"renderer.h"
#include "audio.h"
#include "scene.h"
#include "studiam.h"

#define SCALE 1.0f

void Studiam::Init()
{
	g_Model = new Model();
	g_Model->Load("asset\\model\\studiam_003.obj");

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "pixelLightingPS.cso");

	Renderer::CreatePixelShader(&m_PixelShaderShadow, "BlackShadowPS.cso");


	m_Position = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.007f, 0.007f, 0.007f);

}

void Studiam::Uninit()
{
	/*m_VertexBuffer->Release();
	m_Texture->Release();*/
	g_Model->Unload();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Studiam::Update()
{

}

void Studiam::Draw()
{

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + D3DX_PI /2, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	g_Model->Draw();
	if (g_lightOn == true)
	{
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

	//{

	//	ImGui::Begin("Studiam LightPosition");                          // Create a window called "Hello, world!" and append into it.

	//	
	//	ImGui::Checkbox("Light On Off\n", &g_lightOn);      // Edit bools storing our window open/close state

	//	ImGui::SliderFloat("float\n", &g_light.x, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

	//	ImGui::SliderFloat("float\n", &g_light.y, 0.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

	//	ImGui::SliderFloat("float\n", &g_light.z, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

	//	ImGui::End();
	//}

}


