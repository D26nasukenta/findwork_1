#pragma once
#include "gameobject.h"
class Transition :
    public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	int m_Count;
	float i = 0;
	float j = 0;
	bool key = false;
	bool m_In = false;
	bool m_Finish = false; 

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Start(bool in)
	{
		m_In = in;

		m_Finish = false;
		
		if (m_In == true)
		{
			m_Count = 60;
		}
		else
		{
			m_Count = 0;
		}
	}

	bool GetFinish()
	{
		return m_Finish;
	}
};

