#pragma once
#include "gameobject.h"
#include "Command.h"
class MoveCommand :
    public Command
{
public:
    virtual void execute(GameObject* gameobject)
    {
        gameobject->InputMove();
    }

};

