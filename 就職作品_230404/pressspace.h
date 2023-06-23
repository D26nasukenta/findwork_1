#pragma once

#include "gameobject.h"
class PressSpace :
    public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	float	m_alpha = 0.0f;
	int		m_Frame = 0;
	bool	m_trans = false;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

