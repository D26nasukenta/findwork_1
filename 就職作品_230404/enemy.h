#pragma once
#include "gameobject.h"
#include "BallNotHaveState.h"
#include "state.h"
class ENEMY : public GameObject 
{
private:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11PixelShader* m_PixelShaderShadow = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	
	 
	 State* m_State = nullptr;
	 State* m_NextState = nullptr;

	 BallNotHaveState* m_BallNotHaveState = nullptr;
	 BallNotHaveState* m_NextBallNotHaveState = nullptr;

	 int m_Time = 0;
	 bool m_BallHold = false;
	 class Audio* m_SE;

public:
	ENEMY() {};
	ENEMY(State* State , BallNotHaveState* BallNotHaveState) : m_State(State),m_NextBallNotHaveState(BallNotHaveState)  {};
	void Init();
	
	void Uninit();
	
	void Update();
	
	void Draw();

	void NextState(State* nextstate)
	{
		m_NextState = nextstate;
	}


	void NextBallNotHaveState(BallNotHaveState* nextstate)
	{
		m_NextBallNotHaveState = nextstate;
	}

	void CheckState()
	{
		
		if (m_State != m_NextState)
		{
			m_State = m_NextState;
		}
	}

	void CheckBallNotHaveState()
	{
		if (m_BallNotHaveState != m_NextBallNotHaveState)
		{
			m_BallNotHaveState = m_NextBallNotHaveState;
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

	int GetStateCount()
	{

		return m_State->GetState();
	}
};