#pragma once
#include "MoveCommand.h"
#include "ShootCommand.h"
class Command;
class InputHudler
{
public:

	Command* InputHundle();

private:
	Command* Button_A;
	Command* Button_W;
	Command* Button_S;
	Command* Button_D;

};

