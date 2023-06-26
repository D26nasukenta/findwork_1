#pragma once
#include "Command.h"
#include "gameobject.h"
class StopCommand :
    public Command
{
public:
    virtual void execute(GameObject* gameobject)
    {
        gameobject->StopInput();
    }
};

