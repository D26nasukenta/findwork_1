#pragma once
#include "Command.h"
class ShootReleaseCommand :
    public Command
{
public:
    virtual void execute(GameObject* gameobject)
    {
        gameobject->ShootOutput();
    }
private:

};

