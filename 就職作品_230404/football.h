#pragma once
#include "gameobject.h"
class FootBall :
    public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11PixelShader* m_PixelShaderShadow = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	

	//class Model* g_model = nullptr;
	int m_Frame = 0;
	bool m_kick = false;
	bool m_curvekick = false;
	bool m_Pass = false;
	bool m_DropBall = true;
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	float m_vz = 0.0f;
	float n = -0.81f;
	float m_rx =1.0;
	float m_ry = -(9.8f / 60);
	float m_rz = -(1.0f / 60);



public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Shoot(float vy,float vz);
	void CurveShoot(float vx, float vy, float vz);
	void Pass(float vx, float vz);
	float GetFirstVelY()
	{
		return m_vy;
	}

	float GetFirstVelZ()
	{
		return m_vz;
	}
	void Physics(Scene* scene);

	void SetVel(float vx,float vy, float vz)
	{
		m_vx = vx;
		m_vy = vy;
		m_vz = vz;

	}
};

