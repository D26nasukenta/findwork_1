#pragma once
#include "main.h"
#include "renderer.h"
#include "GameObject.h"
#include <cmath>
#include <random>

#define PI 3.14
#define ONEFLAME 0.01667f


//����
enum class Direction
{
	X_DIRECTION,
	Y_DIRECTION,
	Z_DIRECTION,
};

//�萔�錾
//���d��`��h�����߂�static���g��
const static float radian_vector_normalization = 10.0f;             //���W�A���p�̃x�N�g���𐳋K��

class Effect:public GameObject
{
protected:
	//�G�t�F�N�g�p�ϐ�
    #pragma region Variables For Effect
	int m_Texture = 0;                                              //�e�N�X�`���̓ǂݍ���
	float m_Lifetime = 0.0f;                                        //�p�[�e�B�N���̈�̐����Ă��鎞��
	float m_Usetime = 0.0f;									        //�o�ߎ���
	float m_ParticleGravity = 0.0f;                                 //�p�[�e�B�N���̃O���r�e�B
	float m_ReflectionCoefficient = 0.0f;                           //�p�[�e�B�N���̔��ˌW��
	D3DXVECTOR3 m_AddVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);        //�Z����x�N�g��
	float m_U = 0.0f, m_V = 0.0f;									//UV�l
	D3DXVECTOR2 m_AnimationPatern = D3DXVECTOR2(0.0f, 0.0f);		//�A�j���[�V�����p�^�[��
	float m_OneAnimetionDisplayTime = 0.0f;                         //1���̃A�j���[�V�����̕\������
	float m_OneAnimationDisplayCount = 0.0f;                        //�A�j���[�V�����\�����Ԃ̃J�E���g
	float m_Angle = 0.0f;                                           //��]�p
	float m_AddAngle=0.0f;                                          //���Z����p�x
	D3DXVECTOR3 m_Center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);           //���S���W
	float m_Length = 0.0f;                                          //���a�̒���
	float m_AddLength = 0.0f;                                       //���Z����锼�a

	//�F�n
	float m_NoAlphaShitTime = 0.0f;                                 //���l����������������܂ł̗P�\����
	float m_AlphaShit = 0.0f;                                       //���l�̒l�����炷
	float m_Red = 0.0f;                                             //��
	float m_Green = 0.0f;                                           //��
	float m_Blue = 0.0f;                                            //��
	float m_Alphaw = 0.0f;                                          //���l
    #pragma endregion

public:
	//�Z�b�g�֐�
    #pragma region Effect Set Function
	void SetEffectTexture(int Texture)
	{
		m_Texture = Texture;
	}

	/// <summary>
	/// �G�t�F�N�g���Đ�����鎞�Ԃ�ݒ肷��(�K�{�ݒ�)
	/// </summary>
	void SetEffectLifeTime(float LifeTime) 
	{ 
		m_Lifetime = LifeTime;
	}         

	/// <summary>
	/// �G�t�F�N�g���Đ�����鎞�Ԃ�͈͓����烉���_���ɐݒ肷��(�K�{�ݒ�)
	/// </summary>
	void SetEffectLifeTimeRandom(float MinLifeTime, float MaxLifeTime)
	{
		m_Lifetime = MinLifeTime + (MaxLifeTime - MinLifeTime) + ((float)rand() / RAND_MAX);
	}
	
	/// <summary>
	/// �G�t�F�N�g���󂯂�d�̗͂�
	/// </summary>
	void SetEffectParticleGravity(float ParticleGravity) 
	{
		m_ParticleGravity = ParticleGravity; 
	}

	/// <summary>
    /// �G�t�F�N�g�̔��ˌW�����Z�b�g
    /// </summary>
	void SetReflectionCoefficient(float ReflectionCoefficient) 
	{
		m_ReflectionCoefficient = ReflectionCoefficient; 
	}	  

	/// <summary>
    /// �x�N�g���ɂ���ɉZ����x�N�g��
    /// </summary>
	void SetAddVector(D3DXVECTOR3 AddVector) 
	{ 
		m_AddVector = AddVector; 
	}             

	/// <summary>
	/// �x�N�g���ɂ���Ƀ����_���Ȓl���Z����x�N�g��
	/// </summary>
	void SetAddVectorRandom(D3DXVECTOR3 MinAddVectorRange, D3DXVECTOR3 MaxAddVectorRange)
	{
		m_AddVector.x = MinAddVectorRange.x + (MaxAddVectorRange.x - MinAddVectorRange.x) * ((float)rand() / RAND_MAX);
		m_AddVector.y = MinAddVectorRange.y + (MaxAddVectorRange.y - MinAddVectorRange.y) * ((float)rand() / RAND_MAX);
		m_AddVector.z = MinAddVectorRange.z + (MaxAddVectorRange.z - MinAddVectorRange.z) * ((float)rand() / RAND_MAX);
	}

	/// <summary>
    /// �G�t�F�N�g�̃e�N�X�`����UV�l���Z�b�g
    /// </summary>
	void SetUV(float U, float V)
	{ 
		m_U = U; 
		m_V = V; 
	}

	/// <summary>
    /// �G�t�F�N�g�����������|�W�V�������T�[�N���͈͓̔��ɌĂяo����
    /// </summary>
	void SetPositionCircle(D3DXVECTOR3 Position,float RangeMin,float RangeMax,int CircleDirection)
	{
		float s, t;//���W
		float r;   //���a

		r = RangeMin + (RangeMax - RangeMin) * ((float)rand() / RAND_MAX);

		float theta;
		theta=-PI+(2*PI)*((float)rand() / RAND_MAX);

		s = r * cos(theta);
		t = r * sin(theta);

		//�X�C�b�`
		if (CircleDirection == 0)
		{
			Position.x = Position.x + s;
			Position.y = Position.y + t;
		}
		else if (CircleDirection == 1)
		{
			Position.x = Position.x + s;
			Position.z = Position.z + t;
		}
		else if (CircleDirection == 2)
		{
			Position.y = Position.y + s;
			Position.z = Position.z + t;
		}

		m_Position = Position;
	}

	/// <summary>
	//�~����Ƀ|�W�V������ݒ�
	/// </summary>
	void SetPositionCirclePermiter(D3DXVECTOR3 Center, float Length, float Angle,int Direction)
	{
		//���S���W�Ɋp�x�ƒ������g�p�����~�̈ʒu���Z����
		float radius = Angle * 3.14f / 180.0f;

		//�O�p�Z�����g�p���~�̈ʒu������o��
		float add_s = cos(radius) * Length;
		float add_t = sin(radius) * Length;

		//�����̐ݒ�
		if (Direction == (int)Direction::Y_DIRECTION)
		{
			m_Position.x = Center.x + add_s;
			m_Position.z = Center.z + add_t;
			m_Position.y = Center.y;
		}

		if (Direction == (int)Direction::Z_DIRECTION)
		{
			m_Position.x = Center.x + add_s;
			m_Position.y = Center.y + add_t;
			m_Position.z = Center.z;
		}

		if (Direction == (int)Direction::X_DIRECTION)
		{
			m_Position.y = Center.y + add_s;
			m_Position.z = Center.z + add_t;
			m_Position.x = Center.x;
		}
	}

	/// <summary>
	//���W�A���p�ɂ���Ĉړ�����x�N�g����ݒ�
	/// </summary>
	void SetVectorForRadian(float Angle,int Direction)
	{
		//���S���W�Ɋp�x�ƒ������g�p�����~�̈ʒu���Z����
		float radius = Angle * 3.14f / 180.0f;

		//�O�p�Z�����g�p���~�̈ʒu������o��
		float add_s = cos(radius);
		float add_t = sin(radius);

		if (Direction == (int)Direction::Y_DIRECTION)
		{
			m_Vector.x = add_s / radian_vector_normalization;
			m_Vector.z = add_t / radian_vector_normalization;
		}
		if (Direction == (int)Direction::Z_DIRECTION)
		{
			m_Vector.x = add_s / radian_vector_normalization;
			m_Vector.y = add_t / radian_vector_normalization;
		}
		if (Direction == (int)Direction::X_DIRECTION)
		{
			m_Vector.y = add_s / radian_vector_normalization;
			m_Vector.z = add_t / radian_vector_normalization;
		}
	}

	/// <summary>
	//���a��ݒ�
	/// </summary>
	void SetLength(float Length)
	{ 
		m_Length = Length; 
	}

	/// <summary>
	//���a�������_���Ȓl�Őݒ�
	/// </summary>
	void SetLengthRandom(float MinLength,float MaxLength)
	{
		m_Length = MinLength + (MaxLength - MinLength) + ((float)rand() / RAND_MAX);
	}

	/// <summary>
	//�Z����锼�a��ݒ�
	/// </summary>
	void SetAddLength(float AddLength)
	{
		m_AddLength = AddLength;
	}

	/// <summary>
	//�Z����锼�a�����_���ɐݒ�
	/// </summary>
	void SetAddLengthRandom(float MinAddLength, float MaxAddLength)
	{
		m_AddLength = MinAddLength + (MaxAddLength - MinAddLength) + ((float)rand() / RAND_MAX);
	}

	/// <summary>
	//�Z����锼�a�����_���ɂ�ݒ�
	/// </summary>
	void SetAddAngle(float MinAddAngle, float MaxAddAngle)
	{
		m_AddAngle = MinAddAngle + (MaxAddAngle - MinAddAngle) + ((float)rand() / RAND_MAX);
	}

	/// <summary>
	//��]���钆�S�_��ݒ�
	/// </summary>
	void SetCenter(D3DXVECTOR3 Center)
	{
		m_Center = Center; 
	}

	/// <summary>
	//���K���z�ŃT�[�N����Ƀp�[�e�B�N���𐶐�
	/// </summary>
	void SetPositionCircularConcentration(D3DXVECTOR3 Position, float RangeMin, float RangeMax, int CircleDirection)
	{
		std::random_device seed;
		std::mt19937 engine(seed());            // �����Z���k�E�c�C�X�^�[�@

		float s, t;
		float r;

		float theta;
		theta = -PI + (2 * PI) * ((float)rand() / RAND_MAX);

		 // ����0.0�A�W���΍�1.0�ŕ��z������
		std::normal_distribution<> dist(-RangeMin, RangeMax);

		r = (float)dist(engine);

		s =  r * cos(theta);
		t =  r * sin(theta);

		if (CircleDirection == 1)
		{
			Position.x = Position.x + s;
			Position.y = Position.y + t;
		}
		else if (CircleDirection == 2)
		{
			Position.x = Position.x + s;
			Position.z = Position.z + t;
		}
		else if (CircleDirection == 3)
		{
			Position.y = Position.y + s;
			Position.z = Position.z + t;
		}
		m_Position = Position;
	}
    
	/// <summary>
	//����ɐ��������p�[�e�B�N���̈ʒu�ƃx�N�g����ݒ�
	/// </summary>
	void SetPositionSphere(D3DXVECTOR3 Center,D3DXVECTOR3 Length,float speed)
	{
		float theta= -2*PI + (2*PI) * ((float)rand() / RAND_MAX);
		float p = 1.0f * ((float)rand() / RAND_MAX);
		float phi = asin((2.0f * p) - 1.0f);

		D3DXVECTOR3 position = D3DXVECTOR3(cos(phi)*cos(theta)*Length.x,
			cos(phi)*sin(theta)*Length.y,
			sin(phi)*Length.z);

		m_Vector = D3DXVECTOR3(cos(phi) * cos(theta)*speed, cos(phi) * sin(theta) * speed, sin(phi)* speed);

		m_Position = Center+ position;
	}

	/// <summary>
	//����ɐ��������p�[�e�B�N���̈ʒu�ƃx�N�g����ݒ�
	/// </summary>
	void SetPositionSphereRandomSpeed(D3DXVECTOR3 Center, D3DXVECTOR3 Length, float minspeed,float maxspeed)
	{
		float theta = -2 * PI + (2 * PI) * ((float)rand() / RAND_MAX);
		float p = 1.0f * ((float)rand() / RAND_MAX);
		float phi = asin((2.0f * p) - 1.0f);

		D3DXVECTOR3 position = D3DXVECTOR3(cos(phi) * cos(theta) * Length.x,
			cos(phi) * sin(theta) * Length.y,
			sin(phi) * Length.z);
		float speed = minspeed + (maxspeed - minspeed) + ((float)rand() / RAND_MAX);

		m_Vector = D3DXVECTOR3(cos(phi) * cos(theta) * speed, cos(phi) * sin(theta) * speed, sin(phi) * speed);

		m_Position = Center + position;
	}

	/// <summary>
	//�������������銴�o��ݒ�
	/// </summary>
	void SetAlphaShit(float minshit, float maxshit)
	{
		m_AlphaShit= minshit + (maxshit - minshit) + ((float)rand() / RAND_MAX);
	}

	/// <summary>
	//���l����������������܂ł̗P�\���Ԃ�ݒ�
	/// </summary>
	void SetNoAlphaSihit(float NoAlphaShiftTime)
	{
		m_NoAlphaShitTime = NoAlphaShiftTime;
	}
	#pragma endregion

	//�G�t�F�N�g�֐�
	#pragma region Effect Function
	/// <summary>
    /// �G�t�F�N�g�̈ړ�����
    /// </summary>
	void MoveEffect()
	{
		m_Position.x += m_Vector.x;
		m_Position.y += m_Vector.y;
		m_Position.z += m_Vector.z;
	}

	/// <summary>
	/// �~�^���̈ړ�����
	/// </summary>
	void MoveCircular()
	{
		//���S���W�Ɋp�x�ƒ������g�p�����~�̈ʒu���Z����
		float radius = m_Angle * 3.14f / 180.0f;

		//�O�p�Z�����g�p���~�̈ʒu������o��
		float add_x = cos(radius) * m_Length;
		float add_z = sin(radius) * m_Length;

		//�ړ�����
		m_Position.x = m_Center.x + add_x;
		m_Position.z = m_Center.z + add_z;
		m_Position.y += m_Vector.y;

		m_Angle += m_AddAngle;//�ړ�����p�x���Z����

		m_Length += m_AddLength;//���a���Z����
	}

    /// <summary>
	/// �G�t�F�N�g���g�p����Ă��鎞�Ԃ��Z����
	/// </summary>
	void IncleaseUsetime()
	{
		m_Usetime += ONEFLAME;
	}

	/// <summary>
	/// �G�t�F�N�g�̎g�p���Ԃ��ݒ肵�����C�t�^�C���𒴂������������
	/// </summary>
	void UseTimeOverLife()
	{
		if (m_Lifetime <= m_Usetime)
		{
			SetDestroy();
		}
	}

	/// <summary>
	/// �p�[�e�B�N���̏d�͏���
	/// </summary>
	void ParticleGravity()
	{
		m_Vector.y = m_Vector.y - m_ParticleGravity * m_Usetime / 60;
	}

	/// <summary>
	/// �x�N�g���ɉZ����x�N�g������
	/// </summary>
	void ParticleAddVector()
	{
		m_Vector = m_Vector + m_AddVector * m_Usetime;
	}

	/// <summary>
	/// �G�t�F�N�g�̃A�j���[�V��������(���[�v�Ȃ�)
	/// </summary>
	void ParticleAnimation()
	{
		//�e�N�X�`����X���W
		if (m_OneAnimetionDisplayTime < m_OneAnimationDisplayCount)
		{
			m_AnimationPatern.x++;
			m_OneAnimationDisplayCount = 0.0f;
		}
		else
		{
			m_OneAnimationDisplayCount += ONEFLAME;
		}

		//�e�N�X�`����Y���W
		if (m_AnimationPatern.x >= m_U)
		{
			m_AnimationPatern.y++;
			m_AnimationPatern.x = 0;
		}
	}

	/// <summary>
    /// �G�t�F�N�g�̃A�j���[�V��������(���[�v����)
    /// </summary>
	void ParticleAnimationLoop()
	{
		//�e�N�X�`����X���W
		if (m_OneAnimetionDisplayTime < m_OneAnimationDisplayCount)
		{
			m_AnimationPatern.x++;
			m_OneAnimationDisplayCount = 0.0f;
		}
		else
		{
			m_OneAnimationDisplayCount += ONEFLAME;
		}

		//�e�N�X�`����Y���W
		if (m_AnimationPatern.x >= m_U)
		{
			m_AnimationPatern.x = 0;
		}
	}

	/// <summary>
	/// �G�t�F�N�g�̃A�j���[�V������1�����\������鎞�Ԃ��v�Z
	/// </summary>
	void ParticleOneAnimetionDisplayTimeCaliculate()
	{
		//�ꖇ�ɑ΂���`�掞��(�G�t�F�N�g�̐����Ă鎞��/U�~V�̖���)
		m_OneAnimetionDisplayTime = m_Lifetime / (m_U * m_V);
	}

	/// <summary>
	/// �G�t�F�N�g�̃��[�v�A�j���[�V������1�����\������鎞�Ԃ��v�Z
	/// </summary>
	void ParticleOneLoopAnimationDisplayTimeCaliculate(float DrowTime)
	{
		m_OneAnimetionDisplayTime = DrowTime / (m_U * m_V);
	}

	/// <summary>
	/// �x�N�g���̌�����
	/// </summary>
	void ParticleVectorDecrease(float decreaserate)
	{
		m_Vector *= decreaserate;
	}

	/// <summary>
	/// �⊮����l���擾
	/// </summary>
	float ParticleInterpolationValue(float first, float last, float lifetime)
	{
		float InterPolationValue;
		return InterPolationValue = (last - first) / lifetime / 60;
	}

	/// <summary>
	/// �⊮����l���擾
	/// </summary>
	void ScaleInterPolation(float InterPolition)
	{
		m_Scale.x += InterPolition;
		m_Scale.y += InterPolition;
	}
	#pragma endregion
};