#include "main.h"
#include "InputHandler.h"
#include "input.h"

Command* InputHandler::handleinput()
{
	//�������牺�͈ړ��L�[�{�[�h
	if (GetKeyboardPress(DIK_A))
	{
		return Button_A;

	}
	if (GetKeyboardPress(DIK_D))
	{

		return Button_D;

	}
	if (GetKeyboardPress(DIK_S))
	{
		return Button_S;

	}

	if (GetKeyboardPress(DIK_W))
	{
		return Button_W;
	}

	return NULL;

}
