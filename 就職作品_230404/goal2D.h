#pragma once
#include "gameobject.h"
class Goal2D :
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
	D3DXVECTOR3 m_change = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetAlpha(bool trans);
};

