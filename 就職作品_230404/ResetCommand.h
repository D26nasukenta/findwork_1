#pragma once
#include "Command.h"
#include "gameobject.h"
class ResetCommand :
    public Command
{
public:
    virtual void execute(GameObject* gameobject)
    {
        gameobject->ResetInput();
    }
};

