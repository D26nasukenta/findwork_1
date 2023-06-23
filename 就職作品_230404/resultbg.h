#pragma once
#include "gameobject.h"
class ResultBg :
	public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture[10] ={	NULL, NULL, NULL, 
												NULL ,NULL, NULL, 
												NULL, NULL, NULL, NULL};

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
	float m_alpha = 1.0f;
	float x = 0;
	int m_Frame = 0;
	int m_Selection = 0;
	bool m_trans = false;
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

};

