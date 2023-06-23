#pragma once
#include "main.h"
#include "renderer.h"
#include "GameObject.h"
#include <cmath>
#include <random>

#define PI 3.14
#define ONEFLAME 0.01667f


//向き
enum class Direction
{
	X_DIRECTION,
	Y_DIRECTION,
	Z_DIRECTION,
};

//定数宣言
//多重定義を防ぐ溜めにstaticを使う
const static float radian_vector_normalization = 10.0f;             //ラジアン角のベクトルを正規化

class Effect:public GameObject
{
protected:
	//エフェクト用変数
    #pragma region Variables For Effect
	int m_Texture = 0;                                              //テクスチャの読み込み
	float m_Lifetime = 0.0f;                                        //パーティクルの一つの生きている時間
	float m_Usetime = 0.0f;									        //経過時間
	float m_ParticleGravity = 0.0f;                                 //パーティクルのグラビティ
	float m_ReflectionCoefficient = 0.0f;                           //パーティクルの反射係数
	D3DXVECTOR3 m_AddVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);        //可算するベクトル
	float m_U = 0.0f, m_V = 0.0f;									//UV値
	D3DXVECTOR2 m_AnimationPatern = D3DXVECTOR2(0.0f, 0.0f);		//アニメーションパターン
	float m_OneAnimetionDisplayTime = 0.0f;                         //1枚のアニメーションの表示時間
	float m_OneAnimationDisplayCount = 0.0f;                        //アニメーション表示時間のカウント
	float m_Angle = 0.0f;                                           //回転角
	float m_AddAngle=0.0f;                                          //加算する角度
	D3DXVECTOR3 m_Center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);           //中心座標
	float m_Length = 0.0f;                                          //半径の長さ
	float m_AddLength = 0.0f;                                       //加算される半径

	//色系
	float m_NoAlphaShitTime = 0.0f;                                 //α値をちかちかさせるまでの猶予時間
	float m_AlphaShit = 0.0f;                                       //α値の値をずらす
	float m_Red = 0.0f;                                             //赤
	float m_Green = 0.0f;                                           //緑
	float m_Blue = 0.0f;                                            //青
	float m_Alphaw = 0.0f;                                          //α値
    #pragma endregion

public:
	//セット関数
    #pragma region Effect Set Function
	void SetEffectTexture(int Texture)
	{
		m_Texture = Texture;
	}

	/// <summary>
	/// エフェクトが再生される時間を設定する(必須設定)
	/// </summary>
	void SetEffectLifeTime(float LifeTime) 
	{ 
		m_Lifetime = LifeTime;
	}         

	/// <summary>
	/// エフェクトが再生される時間を範囲内からランダムに設定する(必須設定)
	/// </summary>
	void SetEffectLifeTimeRandom(float MinLifeTime, float MaxLifeTime)
	{
		m_Lifetime = MinLifeTime + (MaxLifeTime - MinLifeTime) + ((float)rand() / RAND_MAX);
	}
	
	/// <summary>
	/// エフェクトが受ける重力の力
	/// </summary>
	void SetEffectParticleGravity(float ParticleGravity) 
	{
		m_ParticleGravity = ParticleGravity; 
	}

	/// <summary>
    /// エフェクトの反射係数をセット
    /// </summary>
	void SetReflectionCoefficient(float ReflectionCoefficient) 
	{
		m_ReflectionCoefficient = ReflectionCoefficient; 
	}	  

	/// <summary>
    /// ベクトルにさらに可算するベクトル
    /// </summary>
	void SetAddVector(D3DXVECTOR3 AddVector) 
	{ 
		m_AddVector = AddVector; 
	}             

	/// <summary>
	/// ベクトルにさらにランダムな値を可算するベクトル
	/// </summary>
	void SetAddVectorRandom(D3DXVECTOR3 MinAddVectorRange, D3DXVECTOR3 MaxAddVectorRange)
	{
		m_AddVector.x = MinAddVectorRange.x + (MaxAddVectorRange.x - MinAddVectorRange.x) * ((float)rand() / RAND_MAX);
		m_AddVector.y = MinAddVectorRange.y + (MaxAddVectorRange.y - MinAddVectorRange.y) * ((float)rand() / RAND_MAX);
		m_AddVector.z = MinAddVectorRange.z + (MaxAddVectorRange.z - MinAddVectorRange.z) * ((float)rand() / RAND_MAX);
	}

	/// <summary>
    /// エフェクトのテクスチャのUV値をセット
    /// </summary>
	void SetUV(float U, float V)
	{ 
		m_U = U; 
		m_V = V; 
	}

	/// <summary>
    /// エフェクトが生成されるポジションをサークルの範囲内に呼び出せる
    /// </summary>
	void SetPositionCircle(D3DXVECTOR3 Position,float RangeMin,float RangeMax,int CircleDirection)
	{
		float s, t;//座標
		float r;   //半径

		r = RangeMin + (RangeMax - RangeMin) * ((float)rand() / RAND_MAX);

		float theta;
		theta=-PI+(2*PI)*((float)rand() / RAND_MAX);

		s = r * cos(theta);
		t = r * sin(theta);

		//スイッチ
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
	//円周上にポジションを設定
	/// </summary>
	void SetPositionCirclePermiter(D3DXVECTOR3 Center, float Length, float Angle,int Direction)
	{
		//中心座標に角度と長さを使用した円の位置を可算する
		float radius = Angle * 3.14f / 180.0f;

		//三角算数を使用し円の位置を割り出す
		float add_s = cos(radius) * Length;
		float add_t = sin(radius) * Length;

		//向きの設定
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
	//ラジアン角によって移動するベクトルを設定
	/// </summary>
	void SetVectorForRadian(float Angle,int Direction)
	{
		//中心座標に角度と長さを使用した円の位置を可算する
		float radius = Angle * 3.14f / 180.0f;

		//三角算数を使用し円の位置を割り出す
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
	//半径を設定
	/// </summary>
	void SetLength(float Length)
	{ 
		m_Length = Length; 
	}

	/// <summary>
	//半径をランダムな値で設定
	/// </summary>
	void SetLengthRandom(float MinLength,float MaxLength)
	{
		m_Length = MinLength + (MaxLength - MinLength) + ((float)rand() / RAND_MAX);
	}

	/// <summary>
	//可算される半径を設定
	/// </summary>
	void SetAddLength(float AddLength)
	{
		m_AddLength = AddLength;
	}

	/// <summary>
	//可算される半径ランダムに設定
	/// </summary>
	void SetAddLengthRandom(float MinAddLength, float MaxAddLength)
	{
		m_AddLength = MinAddLength + (MaxAddLength - MinAddLength) + ((float)rand() / RAND_MAX);
	}

	/// <summary>
	//可算される半径ランダムにを設定
	/// </summary>
	void SetAddAngle(float MinAddAngle, float MaxAddAngle)
	{
		m_AddAngle = MinAddAngle + (MaxAddAngle - MinAddAngle) + ((float)rand() / RAND_MAX);
	}

	/// <summary>
	//回転する中心点を設定
	/// </summary>
	void SetCenter(D3DXVECTOR3 Center)
	{
		m_Center = Center; 
	}

	/// <summary>
	//正規分布でサークル上にパーティクルを生成
	/// </summary>
	void SetPositionCircularConcentration(D3DXVECTOR3 Position, float RangeMin, float RangeMax, int CircleDirection)
	{
		std::random_device seed;
		std::mt19937 engine(seed());            // メルセンヌ・ツイスター法

		float s, t;
		float r;

		float theta;
		theta = -PI + (2 * PI) * ((float)rand() / RAND_MAX);

		 // 平均0.0、標準偏差1.0で分布させる
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
	//球状に生成されるパーティクルの位置とベクトルを設定
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
	//球状に生成されるパーティクルの位置とベクトルを設定
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
	//ちかちかさせる感覚を設定
	/// </summary>
	void SetAlphaShit(float minshit, float maxshit)
	{
		m_AlphaShit= minshit + (maxshit - minshit) + ((float)rand() / RAND_MAX);
	}

	/// <summary>
	//α値をちかちかさせるまでの猶予時間を設定
	/// </summary>
	void SetNoAlphaSihit(float NoAlphaShiftTime)
	{
		m_NoAlphaShitTime = NoAlphaShiftTime;
	}
	#pragma endregion

	//エフェクト関数
	#pragma region Effect Function
	/// <summary>
    /// エフェクトの移動処理
    /// </summary>
	void MoveEffect()
	{
		m_Position.x += m_Vector.x;
		m_Position.y += m_Vector.y;
		m_Position.z += m_Vector.z;
	}

	/// <summary>
	/// 円運動の移動処理
	/// </summary>
	void MoveCircular()
	{
		//中心座標に角度と長さを使用した円の位置を可算する
		float radius = m_Angle * 3.14f / 180.0f;

		//三角算数を使用し円の位置を割り出す
		float add_x = cos(radius) * m_Length;
		float add_z = sin(radius) * m_Length;

		//移動処理
		m_Position.x = m_Center.x + add_x;
		m_Position.z = m_Center.z + add_z;
		m_Position.y += m_Vector.y;

		m_Angle += m_AddAngle;//移動する角度を可算する

		m_Length += m_AddLength;//半径を可算する
	}

    /// <summary>
	/// エフェクトが使用されている時間を可算する
	/// </summary>
	void IncleaseUsetime()
	{
		m_Usetime += ONEFLAME;
	}

	/// <summary>
	/// エフェクトの使用時間が設定したライフタイムを超えたら消す処理
	/// </summary>
	void UseTimeOverLife()
	{
		if (m_Lifetime <= m_Usetime)
		{
			SetDestroy();
		}
	}

	/// <summary>
	/// パーティクルの重力処理
	/// </summary>
	void ParticleGravity()
	{
		m_Vector.y = m_Vector.y - m_ParticleGravity * m_Usetime / 60;
	}

	/// <summary>
	/// ベクトルに可算するベクトル処理
	/// </summary>
	void ParticleAddVector()
	{
		m_Vector = m_Vector + m_AddVector * m_Usetime;
	}

	/// <summary>
	/// エフェクトのアニメーション処理(ループなし)
	/// </summary>
	void ParticleAnimation()
	{
		//テクスチャのX座標
		if (m_OneAnimetionDisplayTime < m_OneAnimationDisplayCount)
		{
			m_AnimationPatern.x++;
			m_OneAnimationDisplayCount = 0.0f;
		}
		else
		{
			m_OneAnimationDisplayCount += ONEFLAME;
		}

		//テクスチャのY座標
		if (m_AnimationPatern.x >= m_U)
		{
			m_AnimationPatern.y++;
			m_AnimationPatern.x = 0;
		}
	}

	/// <summary>
    /// エフェクトのアニメーション処理(ループあり)
    /// </summary>
	void ParticleAnimationLoop()
	{
		//テクスチャのX座標
		if (m_OneAnimetionDisplayTime < m_OneAnimationDisplayCount)
		{
			m_AnimationPatern.x++;
			m_OneAnimationDisplayCount = 0.0f;
		}
		else
		{
			m_OneAnimationDisplayCount += ONEFLAME;
		}

		//テクスチャのY座標
		if (m_AnimationPatern.x >= m_U)
		{
			m_AnimationPatern.x = 0;
		}
	}

	/// <summary>
	/// エフェクトのアニメーションの1枚が表示される時間を計算
	/// </summary>
	void ParticleOneAnimetionDisplayTimeCaliculate()
	{
		//一枚に対する描画時間(エフェクトの生きてる時間/U×Vの枚数)
		m_OneAnimetionDisplayTime = m_Lifetime / (m_U * m_V);
	}

	/// <summary>
	/// エフェクトのループアニメーションの1枚が表示される時間を計算
	/// </summary>
	void ParticleOneLoopAnimationDisplayTimeCaliculate(float DrowTime)
	{
		m_OneAnimetionDisplayTime = DrowTime / (m_U * m_V);
	}

	/// <summary>
	/// ベクトルの減衰率
	/// </summary>
	void ParticleVectorDecrease(float decreaserate)
	{
		m_Vector *= decreaserate;
	}

	/// <summary>
	/// 補完する値を取得
	/// </summary>
	float ParticleInterpolationValue(float first, float last, float lifetime)
	{
		float InterPolationValue;
		return InterPolationValue = (last - first) / lifetime / 60;
	}

	/// <summary>
	/// 補完する値を取得
	/// </summary>
	void ScaleInterPolation(float InterPolition)
	{
		m_Scale.x += InterPolition;
		m_Scale.y += InterPolition;
	}
	#pragma endregion
};