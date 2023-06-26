#include "main.h"
#include "InputHudler.h"
#include "input.h"

Command* InputHudler::InputHundle()
{
	//AWSEDが入力された場合
	if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_W)
		|| GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_D))
	{
		return new MoveCommand();//ムーブコマンドを入れる
	}

	if (GetKeyboardTrigger(DIK_SPACE))
	{

		return new ResetCommand();
	}

	return new StopCommand();
}
