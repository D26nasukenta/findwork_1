#include "main.h"
#include "InputHudler.h"
#include "input.h"
Command* InputHudler::InputHundle()
{
	if (GetKeyboardPress(DIK_A))
	{
		return Button_A;
	}
	if (GetKeyboardPress(DIK_W))
	{
		return Button_W;
	}
	if (GetKeyboardPress(DIK_S))
	{
		return Button_S;
	}
	if (GetKeyboardPress(DIK_D))
	{
		return Button_A;
	}

	return nullptr;
}
