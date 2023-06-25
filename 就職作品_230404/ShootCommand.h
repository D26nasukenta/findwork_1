#pragma once
#include "Command.h"
#include "gameobject.h"
class ShootCommand :
    public Command
{
public:

    virtual void execute(GameObject* gameobject)
    {
        gameobject->ShootInput();
    }
};

