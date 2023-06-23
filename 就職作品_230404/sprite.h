#pragma once
#include "main.h"
#include "GameObject.h"

class Sprite
{
private:


public:
	static void InitSprite();
	static void UninitSprite();

	static void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
	static void DrawSprite(int texNo, float X, float Y, float Width, float Height,float U, float V, float UW, float VH,D3DXVECTOR4 Color, float Rot);
	static void DrawSpriteBillBoard(int texNo, D3DXVECTOR3 Position,D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale,  float U, float V, float UW, float VH, D3DXVECTOR4 Color, float Rot);
	static void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
};
