#pragma once
#include "gameobject.h"

#define PARTICLE_MAX		(100)				// パーティクルの数
struct PARTICLE
{
	int		status;		// 状態
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3	vel;		// 速度
	D3DXVECTOR3	acc;		// 加速度
	D3DXVECTOR3	size;		// 大きさ
	int		life;		// 消滅時間(フレーム数)
	bool	random ;
	int texturerandom ;

	D3DXVECTOR4 col;		// 色
};


class Particle :
    public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;
	ID3D11ShaderResourceView* m_Texture2 = NULL;
	ID3D11ShaderResourceView* m_Texture3 = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
	// 変数
	PARTICLE g_Particle[PARTICLE_MAX];
	//class Model* g_model = nullptr;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void CreateParticle(D3DXVECTOR3 position,D3DXVECTOR3 velocity,
						D3DXVECTOR3 accel,D3DXVECTOR3 size,
						D3DXVECTOR4 col,int life , int texturerandom);
};

