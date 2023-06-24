#pragma once
#include "gameobject.h"
class SkyDome :
    public GameObject
{

private:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;


	State* m_State = nullptr;
	State* m_NextState = nullptr;

	int m_Time = 0;

public:

	void Init();

	void Uninit();

	void Update();

	void Draw();



};

