#pragma once
#include "gameobject.h"
#include "keeperstate.h"
class GoalKeeper :
    public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	ID3D11PixelShader* m_PixelShaderShadow = nullptr;

	KeeperState* m_State = nullptr;
	KeeperState* m_NextState = nullptr;

	int m_Time = 0;
	bool m_BallHold = false;
	bool m_Jump = false;
	float m_ry = -(9.8f / 60);
	float m_vy =1.8f;
public:
	GoalKeeper() {};
	GoalKeeper(KeeperState* State) : m_State(State) {};
	void Init();

	void Uninit();

	void Update();

	void Draw();

	void NextState(KeeperState* nextstate)
	{
		m_NextState = nextstate;
	}

	void CheckState()
	{

		if (m_State != m_NextState)
		{
			m_State = m_NextState;
		}
	}

	bool GetHoldState()
	{
		return m_BallHold;
	}
	void SetHoldState(bool state)
	{
		m_BallHold = state;
	}
	bool GetJumpState()
	{
		return m_Jump;
	}
	void SetJumpState(bool state)
	{
		m_Jump = state;
	}
	void GoalKeeperMove();
};

