#pragma once
#include "MoveCommand.h"
#include "ShootCommand.h"
#include "StopCommand.h"
#include "ResetCommand.h"
#include "ShootReleaseCommand.h"
class Command;
class InputHudler
{
public:

	Command* InputHundle();

private:
	int m_shotFrame = 0;

};

