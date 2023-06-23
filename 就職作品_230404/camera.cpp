#include <math.h>
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "football.h"
#include "studiam.h"

bool change = false;
//static D3DXVECTOR3 g_PlayerPos;

void Camera::Init()
{
	//g_PlayerPos = g_player->GetPosition();

	m_Position = D3DXVECTOR3(0.0f, 4.0f, -10.0f);
	m_Target = D3DXVECTOR3(0.0f, 8.0f, 0.0f);
}


void Camera::Uninit()
{

}

void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	
	if (scene->GetSceneNumber() == 1)
	{
		TitleCamera(scene);

	}
	else if (scene->GetSceneNumber() >= 2)
	{

		GameCamera(scene);
	}

	//m_Position = D3DXVECTOR3(0.0f, 4.0f, -10.0f);
	//m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//ファーストパーソンビュー

	/*m_Target = PlayerPos + PlayerForward;
	m_Position = PlayerPos;*/

}

void Camera::Draw()
{

	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリクス設定

	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);//描画距離がある


	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
	
	//カメラの座標をシェーダーへ渡す
	Renderer::SetCameraPosition(m_Position);
}

void Camera::GameCamera(Scene* scene)
{
	
	PLAYER* player = scene->GetGameObject<PLAYER>(1);
	FootBall* football = scene->GetGameObject<FootBall>(1);
	D3DXVECTOR3 PlayerPos = player->GetPosition();
	D3DXVECTOR3 footballPos = football->GetPosition();
	D3DXVECTOR3 PlayerForward = player->GetForward();
	D3DXVECTOR3 Both;

	D3DXVec3Lerp(&Both, &footballPos, &PlayerPos, 2);


	if (GetKeyboardPress(DIK_SPACE))
	{
		change = false;
	}

	if (GetKeyboardPress(DIK_1))
	{

		change = true;
	}

	if (change == true)
	{

		if (GetKeyboardPress(DIK_UP))
		{
			m_CameraVel.y += 0.5f;

		}

		//サードパーソンビュー
		m_Target = player->GetPosition();
		m_Position = D3DXVECTOR3(-55.0f, 40.0f + m_CameraVel.y, -50.0f);

	}
	else
	{
		//トップビュー
		m_Target = PlayerPos + D3DXVECTOR3(0.0f, 3.0f, 10.0f);
		m_Position = PlayerPos + D3DXVECTOR3(0.0f, 10.0f, -9.0f);


	}

}

void Camera::TitleCamera(Scene* scene)
{
	Studiam* studiam = scene->GetGameObject<Studiam>(1);
	D3DXVECTOR3 StudiamPos = studiam->GetPosition();

	m_Target = StudiamPos ;
	m_Position = StudiamPos + D3DXVECTOR3(-300.0f + m_CameraVel.x , 200.0f, 300.0f + m_CameraVel.z);

	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	m_Rotate += 0.1f;

	//	m_CameraVel.x += cosf(m_Rotate) * 50.0f;
	//	m_CameraVel.z += sinf(m_Rotate) * 50.0f;
	//}


}

bool Camera::ChecView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invvp;
	vp = m_ViewMatrix * m_ProjectionMatrix;

	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);


	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;
	
	v = Position - m_Position;


	//左面判定
	{

		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;

		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);
		if (D3DXVec3Dot(&n, &v) < 0.01f)
		{
			return false;
		}
	}				

	D3DXVECTOR3  v3, v4;



	//左面判定
	{

		v3 = wpos[1] - m_Position;
		v4 = wpos[3] - m_Position;

		D3DXVec3Cross(&n, &v3, &v4);
		D3DXVec3Normalize(&n, &n);
		
		if (D3DXVec3Dot(&n, &v) > -0.1f)
		{
			return false;
		}
	}

	return true;

}