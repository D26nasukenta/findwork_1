#pragma once
#include "gameobject.h"
class Studiam :
    public GameObject
{

private:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11PixelShader* m_PixelShaderShadow = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	bool g_lightOn = false;


public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

};

