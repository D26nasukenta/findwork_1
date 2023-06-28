#pragma once
#include "MoveCommand.h"
#include "StopCommand.h"
#include "ResetCommand.h"
#include "MovePadCommand.h"
class Command;
class InputHudler
{
public:

	Command* InputHundle();

private:
	int m_shotFrame = 0;

};

