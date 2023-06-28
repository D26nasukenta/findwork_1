#pragma once
#include "Command.h"
#include "gameobject.h"
class MovePadCommand :
    public Command
{
public:
    virtual void execute(GameObject* gameobject)
    {
        gameobject->InputPadMove();
    }
};

