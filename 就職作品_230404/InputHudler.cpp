#include "main.h"
#include "InputHudler.h"
#include "input.h"

Command* InputHudler::InputHundle()
{
	//AWSEDが入力された場合
	if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_W)
		|| GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_D))
	{
		return new MoveCommand();//InputMove
	}

	//ゲームパッド
	if (IsButtonPressed(0, BUTTON_UP) || IsButtonPressed(0, BUTTON_RIGHT)
		|| IsButtonPressed(0, BUTTON_DOWN) || IsButtonPressed(0, BUTTON_LEFT)) 
	{
		return new MovePadCommand();//InputPadMove
	}

	if (GetKeyboardTrigger(DIK_SPACE))
	{

		return new ResetCommand();
	}


	return new StopCommand();
}
