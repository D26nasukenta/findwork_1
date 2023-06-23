#pragma once

#include <string>

#include "gameobject.h"

class PLAYER : public GameObject
{
private:
	class AnimationModel* m_Model ;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11PixelShader* m_PixelShaderShadow;
	ID3D11InputLayout* m_VertexLayout;

	int m_Frame[3] = {0,0,0};
	int m_ShotFrame = 0;
	int m_Step = 0;
	float m_Brendlate;

	float m_Speed = 1.2f;
	bool m_HoldBall = false;
	bool m_Kickform = false;
	bool m_dribble = false;
	bool m_idlechange = false;
	D3DXVECTOR3 m_Power;
	std::string	m_AnimationName;

	class Audio* m_SE;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool GetPlayerHold()
	{
		return m_HoldBall;
	}
	void SetHoldState(bool state)
	{
		m_HoldBall = state;
	}

	bool GetPlayerKick()
	{
		return m_Kickform;
	}

	int GetTutorialStep()
	{
		return m_Step;
	}

	void SetKickState(bool state)
	{
		m_Kickform = state;
	}
	//ボールをホールドしてるとき
	void playerholdball(Scene* scene);
	
	//チュートリアルシーンのとき
	void playerTutolialMove(Scene* scene);

	//プレイヤーの行動範囲
	void PlayerRange(Scene* scene);


	//プレイヤーの基本的な動き
	void playermove();
	
};