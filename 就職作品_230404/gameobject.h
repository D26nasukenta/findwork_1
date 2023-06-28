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

	// �����ւ̃x�N�g��(���s����/�_�����ŕς��Ă݂悤)
	D3DXVECTOR4 g_light = D3DXVECTOR4(-10.0f, 10.0f, 0.0f, 0.0f);//�f�B���N�V���i�����C�g�̕������w�肷��;
	D3DXMATRIX		g_MatrixShadow;		// �e�s��

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

	GameObject() {};//�R���X�g���N�^

	virtual ~GameObject() {}//�f�X�g���N�^

	virtual void Init() = 0;		//�������z�֐�
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

	D3DXVECTOR3 GetForward()//�O�x�N�g���̎擾
	{
		D3DXMATRIX rot;//�}�g���N�X�̒�`��float�� 4�~4�̍\���́@�p����\���ϐ�

		D3DXMatrixRotationYawPitchRoll//rotation�ϐ�����}�g���b�N�X���쐬
		(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//�g�[���X�Ȃ�y,x,z�̏���
		D3DXVECTOR3 forward;
		//31,32,33�����o���ƑO�����̃x�N�g����Z+����
		//11,12,13����X+����
		//21,22,23����Y+����
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetUP()//�O�x�N�g���̎擾
	{
		D3DXMATRIX rot;//�}�g���N�X�̒�`��float�� 4�~4�̍\���́@�p����\���ϐ�

		D3DXMatrixRotationYawPitchRoll//rotation�ϐ�����}�g���b�N�X���쐬
		(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//�g�[���X�Ȃ�y,x,z�̏���
		D3DXVECTOR3 forward;
		//31,32,33�����o���ƑO�����̃x�N�g����Z+����
		//11,12,13����X+����
		//21,22,23����Y+����
		forward.x = rot._21;
		forward.y = rot._22;
		forward.z = rot._23;

		return forward;
	}

	D3DXVECTOR3 GetRIGHT()//�O�x�N�g���̎擾
	{
		D3DXMATRIX rot;//�}�g���N�X�̒�`��float�� 4�~4�̍\���́@�p����\���ϐ�

		D3DXMatrixRotationYawPitchRoll//rotation�ϐ�����}�g���b�N�X���쐬
		(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//�g�[���X�Ȃ�y,x,z�̏���
		D3DXVECTOR3 forward;
		//31,32,33�����o���ƑO�����̃x�N�g����Z+����
		//11,12,13����X+����
		//21,22,23����Y+����
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

	//�ړ��p
	void InputMove()
	{
		float m_Speed = 1.2f;

		//�V���[�g�{�^���������Ă��Ȃ����
		if (m_Kickform == false)
		{
			//�������牺�͈ړ��L�[�{�[�h
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

	//�ړ��p
	void InputPadMove()
	{
		//�V���[�g�{�^���������Ă��Ȃ����
		if (m_Kickform == false)
		{
			if (IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, BUTTON_RIGHT)
				|| IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, BUTTON_LEFT))  //�Q�[���p�b�h
			{
				m_Rotation.y = -(GetLeftStickAngle(0) - D3DX_PI / 2);
				m_Position += GameObject::GetForward() * 0.5f;
				m_dribble = true;
			}
		}

	}

	//�{�^����������Ă��Ȃ��Ƃ�
	void StopInput()
	{
		//�v���C���[�̃��[�V�����`�F���W
		if ( (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_W)
			&& GetKeyboardPress(DIK_S) && GetKeyboardPress(DIK_D)) == false)
		{
			m_dribble = false;

		}
	}

	//�{�[���Ȃǂ����Z�b�g
	void ResetInput()
	{
		m_AnimationName = "Idle";
		m_idlechange = false;
	}

	private:

};
