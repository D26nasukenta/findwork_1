#pragma once
#include "manager.h"
#include "renderer.h"
#include "gameobject.h"
class Camera : public GameObject
{

private:
	
	D3DXVECTOR3 m_Target;
	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX	m_ProjectionMatrix;
	D3DXVECTOR3 m_CameraVel;
	float m_Rotate = 0.0f;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void GameCamera(Scene* scene);
	void TitleCamera(Scene* scene);

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	bool ChecView(D3DXVECTOR3 Position);


};