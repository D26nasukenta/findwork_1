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

	if (GetKeyboardPress(DIK_J) || IsButtonPressed(0, BUTTON_B))
	{
		m_shotFrame++;
		return new ShootCommand();
	}
	if (GetKeyboardRelease(DIK_J) || IsButtonReleased(0, BUTTON_B) || m_shotFrame >= 40)//離した時に弾を蹴る
	{
		return new ShootReleaseCommand();
	}

	return new StopCommand();
}
