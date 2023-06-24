#pragma once
#include "gameobject.h"
class Score :
	public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	int m_Count ;
	int m_Score;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetScore(int count)
	{
		m_Score = count;
	}

	int GetScore()
	{
		return m_Score;
	}

};

