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

	if (GetKeyboardPress(DIK_J) || IsButtonPressed(0, BUTTON_B))
	{
		m_shotFrame++;
		return new ShootCommand();
	}
	if (GetKeyboardRelease(DIK_J) || IsButtonReleased(0, BUTTON_B) || m_shotFrame >= 40)//���������ɒe���R��
	{
		return new ShootReleaseCommand();
	}

	return new StopCommand();
}
