#include "main.h"
#include "InputHudler.h"
#include "input.h"

Command* InputHudler::InputHundle()
{
	//AWSED�����͂��ꂽ�ꍇ
	if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_W)
		|| GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_D))
	{
		return new MoveCommand();//���[�u�R�}���h������
	}

	if (GetKeyboardTrigger(DIK_SPACE))
	{

		return new ResetCommand();
	}

	return new StopCommand();
}
