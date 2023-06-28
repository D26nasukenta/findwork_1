#pragma once
#include "main.h"
#include "input.h"

class GameObject
{
protected:
	bool m_Destroy = false;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_Vector;

	// 光源へのベクトル(平行光源/点光源で変えてみよう)
	D3DXVECTOR4 g_light = D3DXVECTOR4(-10.0f, 10.0f, 0.0f, 0.0f);//ディレクショナルライトの方向を指定する;
	D3DXMATRIX		g_MatrixShadow;		// 影行列

	class Model* g_Model = nullptr;

	class Scene* g_scene = nullptr;

	/*ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;*/

	bool m_dribble = false;
	bool m_idlechange = false;
	bool m_Kickform = false;
	std::string	m_AnimationName;
	int m_ShotFrame = 0;
	D3DXVECTOR3 m_Power;

public:

	GameObject() {};//コンストラクタ

	virtual ~GameObject() {}//デストラクタ

	virtual void Init() = 0;		//純粋仮想関数
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;



	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy == true)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	void SetPosition(D3DXVECTOR3 Position)
	{
		m_Position = Position;
	}

	D3DXVECTOR3 GetPosition()
	{

		return m_Position;
	}

	void SetMovement(D3DXVECTOR3 Movement)
	{
		m_Position += Movement;
	}

	void SetRotation(D3DXVECTOR3 Rotation)
	{
		m_Rotation = Rotation;
	}

	D3DXVECTOR3 GetRotation()
	{

		return m_Rotation;
	}

	void SetRotate(D3DXVECTOR3 Rotate)
	{
		m_Rotation.x += Rotate.x;
		m_Rotation.y += Rotate.y;
		m_Rotation.z += Rotate.z;
	}

	D3DXVECTOR3 GetForward()//前ベクトルの取得
	{
		D3DXMATRIX rot;//マトリクスの定義はfloatが 4×4の構造体　姿勢を表す変数

		D3DXMatrixRotationYawPitchRoll//rotation変数からマトリックスを作成
		(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//トーラスならy,x,zの順で
		D3DXVECTOR3 forward;
		//31,32,33を取り出すと前方向のベクトルにZ+方向
		//11,12,13だとX+方向
		//21,22,23だとY+方向
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetUP()//前ベクトルの取得
	{
		D3DXMATRIX rot;//マトリクスの定義はfloatが 4×4の構造体　姿勢を表す変数

		D3DXMatrixRotationYawPitchRoll//rotation変数からマトリックスを作成
		(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//トーラスならy,x,zの順で
		D3DXVECTOR3 forward;
		//31,32,33を取り出すと前方向のベクトルにZ+方向
		//11,12,13だとX+方向
		//21,22,23だとY+方向
		forward.x = rot._21;
		forward.y = rot._22;
		forward.z = rot._23;

		return forward;
	}

	D3DXVECTOR3 GetRIGHT()//前ベクトルの取得
	{
		D3DXMATRIX rot;//マトリクスの定義はfloatが 4×4の構造体　姿勢を表す変数

		D3DXMatrixRotationYawPitchRoll//rotation変数からマトリックスを作成
		(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//トーラスならy,x,zの順で
		D3DXVECTOR3 forward;
		//31,32,33を取り出すと前方向のベクトルにZ+方向
		//11,12,13だとX+方向
		//21,22,23だとY+方向
		forward.x = rot._11;
		forward.y = rot._12;
		forward.z = rot._13;

		return forward;
	}

	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vx;

		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		return vx * 0.5f;

	}

	D3DXVECTOR3	GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vz;

		vz.x = world._31;
		vz.y = world._32;
		vz.z = world._33;

		return vz * 0.5f;
	}

	D3DXVECTOR3	GetObbY()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vy;

		vy.x = world._21;
		vy.y = world._22;
		vy.z = world._23;

		return vy;
	}

	inline void SetRandomRangeScale(D3DXVECTOR3 Scale, float MaxRange, float MinRange)
	{
		float random = (MaxRange - MinRange) * ((float)rand() / RAND_MAX);
		m_Scale.x = Scale.x + random;
		m_Scale.y = Scale.y + random;
		m_Scale.z = Scale.z + random;
	}

	//移動用
	void InputMove()
	{
		float m_Speed = 1.2f;

		//シュートボタンを押していなければ
		if (m_Kickform == false)
		{
			//ここから下は移動キーボード
			if (GetKeyboardPress(DIK_A))
			{
				m_Rotation.y = -D3DX_PI / 2;
				m_Position.x -= m_Speed * 0.6;
			
			}
			

			if (GetKeyboardPress(DIK_D))
			{

				m_Rotation.y = D3DX_PI / 2;

				m_Position.x += m_Speed * 0.6;
				

			}

			if (GetKeyboardPress(DIK_S))
			{
				m_Rotation.y = D3DX_PI;

				m_Position.z -= m_Speed * 0.3;

			}

			if (GetKeyboardPress(DIK_W))
			{
				m_Rotation.y = 0.0f;
				m_Position.z += m_Speed * 0.6;
			}

		}
	}

	//移動用
	void InputPadMove()
	{
		//シュートボタンを押していなければ
		if (m_Kickform == false)
		{
			if (IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, BUTTON_RIGHT)
				|| IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, BUTTON_LEFT))  //ゲームパッド
			{
				m_Rotation.y = -(GetLeftStickAngle(0) - D3DX_PI / 2);
				m_Position += GameObject::GetForward() * 0.5f;
				m_dribble = true;
			}
		}

	}

	//ボタンを押されていないとき
	void StopInput()
	{
		//プレイヤーのモーションチェンジ
		if ( (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_W)
			&& GetKeyboardPress(DIK_S) && GetKeyboardPress(DIK_D)) == false)
		{
			m_dribble = false;

		}
	}

	//ボールなどをリセット
	void ResetInput()
	{
		m_AnimationName = "Idle";
		m_idlechange = false;
	}

	private:

};
