#pragma once
#include "gameobject.h"
class Goal :
    public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	ID3D11PixelShader* m_PixelShaderShadow = nullptr;
	

	int m_Frame = 0;
	class Audio* m_SE;
	bool m_goalCheck = false;
	int m_Score;

public:

	void Init();

	void Uninit();

	void Update();

	void Draw();

	void GoalJudge();

	bool GetGoalCheck()
	{
		return m_goalCheck;
	}
};

