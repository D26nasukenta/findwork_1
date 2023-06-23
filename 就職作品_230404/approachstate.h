#pragma once
#include "state.h"
class ENEMY;
class ApproachState :
    public State
{
public:
    ApproachState(ENEMY* penemy) : m_Enemy(penemy) {};

    void   Init();
    void   Uninit();
    void   Update();
    int    GetState()
    {
        return StateCount;
    };

private:
    ENEMY* m_Enemy;
    int m_Frame = 0;

};

